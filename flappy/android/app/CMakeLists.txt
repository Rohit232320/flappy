cmake_minimum_required(VERSION 3.10.2)
project("flappy")

# Locate Raylib (adjust path if raylib is elsewhere in your repo)
set(RAYLIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../raylib")

add_library(main SHARED
            main.c) # Replace main.c with your actual source filename

target_include_directories(main PRIVATE 
                           ${RAYLIB_PATH}/src)

target_link_libraries(main
                      android
                      log
                      EGL
                      GLESv2
                      m)
