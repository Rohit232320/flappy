cmake_minimum_required(VERSION 3.10.2)
project(FlappyBird)

# Define where your raylib source code is
# Adjust this path to where 'raylib/src' is located in your repo
set(RAYLIB_SRC "../../../raylib/src") 

add_library(main SHARED
    ../../../flappy/flappy.c  # Your actual C game file
    ${RAYLIB_SRC}/platforms/rcore_android.c # Required for Android
)

target_include_directories(main PRIVATE ${RAYLIB_SRC})

# Link necessary Android system libraries
target_link_libraries(main android log EGL GLESv2 m)
