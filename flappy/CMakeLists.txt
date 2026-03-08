cmake_minimum_required(VERSION 3.11)

project(FlappyBird VERSION 1.0.0 LANGUAGES C)

# Set up C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Configure build options for Raylib (we want a static library)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Raylib FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0
)
FetchContent_MakeAvailable(raylib)

# Gather source files
set(SOURCES
    src/main.c
    src/pipe.c
    src/bird.c
    src/bg_gnd.c
    src/score.c
)

# On Android, Raylib uses a shared library for the main application,
# loaded by the NativeActivity.
if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
    target_include_directories(${PROJECT_NAME} PRIVATE include)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib EGL GLESv2 android log)
    
    # Android's NativeActivity ordinarily expects exactly libmain.so
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")

# PC (Windows/Linux/macOS) builds an executable
else()
    # Add GUI flag for Windows to suppress terminal console (optional)
    if(WIN32)
        add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
    else()
        add_executable(${PROJECT_NAME} ${SOURCES})
    endif()

    target_include_directories(${PROJECT_NAME} PRIVATE include)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()
