cmake_minimum_required(VERSION 3.10.2)
project(FlappyBird)

# Define where Raylib is located relative to this file
set(RAYLIB_SRC "../../../raylib/src")

add_library(main SHARED
    ../../../flappy/flappy.c  # Path to your game code
    ${RAYLIB_SRC}/platforms/rcore_android.c
)

target_include_directories(main PRIVATE ${RAYLIB_SRC})
target_link_libraries(main android log EGL GLESv2 m)
