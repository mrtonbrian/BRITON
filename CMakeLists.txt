cmake_minimum_required(VERSION 3.13)  # CMake version check
project(Chess-Engine-Cpp)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES attack.cpp bitboards.cpp board.cpp evaluate.cpp hashkey.cpp init.cpp io.cpp main.cpp makemove.cpp misc.cpp move.cpp movegen.cpp perft.cpp pvtable.cpp search.cpp validate.cpp uci.cpp)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g -W -Wall -Wextra -pedantic")

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(chess ${SOURCE_FILES})
