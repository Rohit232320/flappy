cmake_minimum_required(VERSION 3.10.2)
project(FlappyBird)

# Path to the root of your repository
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

# Define where Raylib source is (adjust if your raylib folder is named differently)
set(RAYLIB_SRC "${REPO_ROOT}/raylib/src")

add_library(main SHARED
    # This points to flappy/flappy/src/main.c
    ${REPO_ROOT}/flappy/src/main.c  
    ${RAYLIB_SRC}/platforms/rcore_android.c
)

# Include Raylib headers
target_include_directories(main PRIVATE ${RAYLIB_SRC})

# Link Android system libraries
target_link_libraries(main android log EGL GLESv2 m)
