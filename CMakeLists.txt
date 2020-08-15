cmake_minimum_required(VERSION 3.13)  # CMake version check
project(Chess-Engine-Cpp)
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project src as source file
set(SOURCE_FILES src/main.cpp src/Position.cpp src/Position.h src/Bitboard.h src/movegen.h src/misc.h src/misc.cpp src/Bitboard.cpp src/init.cpp src/init.h src/movegen.cpp src/bitops.cpp src/bitops.h src/bitops.cpp src/bitops.h src/perft.cpp src/perft.h src/TranspositionTable.cpp src/TranspositionTable.h)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -W -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -W -Wall -Wextra -pedantic")

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(briton ${SOURCE_FILES})
