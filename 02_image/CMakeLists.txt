cmake_minimum_required(VERSION 3.7)
project(SDL2Test)

set(SDL2_PATH "D:/usr/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(SDL2Test ./02_getting_image.cpp)

target_link_libraries(SDL2Test ${SDL2_LIBRARY})
