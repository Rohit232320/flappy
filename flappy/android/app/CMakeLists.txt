cmake_minimum_required(VERSION 3.10.2)
project(FlappyBird)

# Root directory of your repository relative to this file
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
set(RAYLIB_SRC "${REPO_ROOT}/raylib/src")
set(GAME_SRC_DIR "${REPO_ROOT}/flappy/src")

add_library(main SHARED
    # Game Source Files from your flappy/src directory
    "${GAME_SRC_DIR}/main.c"
    "${GAME_SRC_DIR}/bird.c"
    "${GAME_SRC_DIR}/pipe.c"
    "${GAME_SRC_DIR}/bg_gnd.c"
    "${GAME_SRC_DIR}/score.c"
    
    # Required Raylib Android platform file
    "${RAYLIB_SRC}/platforms/rcore_android.c"
)

# Include directories for Raylib and your own headers
target_include_directories(main PRIVATE 
    "${RAYLIB_SRC}"
    "${REPO_ROOT}/flappy/include"
)

# Link required Android system libraries
target_link_libraries(main android log EGL GLESv2 m)
