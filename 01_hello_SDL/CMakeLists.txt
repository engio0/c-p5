cmake_minimum_required(VERSION 3.7)
project(SDL2Test)
set(CMAKE_CXX_STANDARD 11)
 
# set(CMAKE_MODULE_PATH "D:/ProgramFiles/CMake/share/cmake-3.11/Modules")
#
#   set(SDL2_INCLUDE_DIRS "D:/lib/mingw/x86_64-w64-mingw32/include/SDL2")
#   set(SDL2_LIBRARIES "D:/lib/mingw/x86_64-w64-mingw32/lib")
# set(SDL2_PATH "D:/lib/mingw/x86_64-w64-mingw32")

set(SDL2_PATH "D:/lib/mingw/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# link_directories(${SDL2_LIBRARIES})

add_executable(SDL2Test 01_hello_SDL.cpp)

target_link_libraries(SDL2Test ${SDL2_LIBRARY})
