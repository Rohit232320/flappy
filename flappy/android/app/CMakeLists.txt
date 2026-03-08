cmake_minimum_required(VERSION 3.10.2)
project(FlappyBird)

# According to your logs, the root is 3 levels up from /android/app
# We use quotes to ensure paths with spaces don't break the build
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
set(RAYLIB_SRC "${REPO_ROOT}/raylib/src")
set(GAME_SRC "${REPO_ROOT}/flappy/src")

add_library(main SHARED
    # Game Logic (from your screenshot)
    "${GAME_SRC}/main.c"
    "${GAME_SRC}/bird.c"
    "${GAME_SRC}/pipe.c"
    "${GAME_SRC}/bg_gnd.c"
    "${GAME_SRC}/score.c"
    
    # Android Platform glue from Raylib
    "${RAYLIB_SRC}/platforms/rcore_android.c"
)

# Tell the compiler where to find headers (.h files)
target_include_directories(main PRIVATE 
    "${RAYLIB_SRC}"
    "${REPO_ROOT}/flappy/include"
)

# Standard Android libraries needed for Raylib
target_link_libraries(main android log EGL GLESv2 m)
