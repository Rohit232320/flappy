cmake_minimum_required(VERSION 3.10.2)
project(FlappyBird)

# We are in: flappy/android/app
# We need to go up 3 levels to reach the root where 'raylib' and 'flappy' live
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
set(RAYLIB_SRC "${REPO_ROOT}/raylib/src")
set(GAME_SRC "${REPO_ROOT}/flappy/src")

add_library(main SHARED
    # Your game files from the screenshot
    "${GAME_SRC}/main.c"
    "${GAME_SRC}/bird.c"
    "${GAME_SRC}/pipe.c"
    "${GAME_SRC}/bg_gnd.c"
    "${GAME_SRC}/score.c"
    
    # Raylib Android support
    "${RAYLIB_SRC}/platforms/rcore_android.c"
)

target_include_directories(main PRIVATE 
    "${RAYLIB_SRC}"
    "${REPO_ROOT}/flappy/include"
)

target_link_libraries(main android log EGL GLESv2 m)
