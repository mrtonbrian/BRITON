# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/99/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/99/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brianton/Desktop/Chess-Engine-Cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BRITON.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BRITON.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BRITON.dir/flags.make

CMakeFiles/BRITON.dir/src/main.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BRITON.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/main.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/main.cpp

CMakeFiles/BRITON.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/main.cpp > CMakeFiles/BRITON.dir/src/main.cpp.i

CMakeFiles/BRITON.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/main.cpp -o CMakeFiles/BRITON.dir/src/main.cpp.s

CMakeFiles/BRITON.dir/src/Position.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/Position.cpp.o: ../src/Position.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BRITON.dir/src/Position.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/Position.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/Position.cpp

CMakeFiles/BRITON.dir/src/Position.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/Position.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/Position.cpp > CMakeFiles/BRITON.dir/src/Position.cpp.i

CMakeFiles/BRITON.dir/src/Position.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/Position.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/Position.cpp -o CMakeFiles/BRITON.dir/src/Position.cpp.s

CMakeFiles/BRITON.dir/src/misc.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/misc.cpp.o: ../src/misc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BRITON.dir/src/misc.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/misc.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/misc.cpp

CMakeFiles/BRITON.dir/src/misc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/misc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/misc.cpp > CMakeFiles/BRITON.dir/src/misc.cpp.i

CMakeFiles/BRITON.dir/src/misc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/misc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/misc.cpp -o CMakeFiles/BRITON.dir/src/misc.cpp.s

CMakeFiles/BRITON.dir/src/Bitboard.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/Bitboard.cpp.o: ../src/Bitboard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/BRITON.dir/src/Bitboard.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/Bitboard.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/Bitboard.cpp

CMakeFiles/BRITON.dir/src/Bitboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/Bitboard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/Bitboard.cpp > CMakeFiles/BRITON.dir/src/Bitboard.cpp.i

CMakeFiles/BRITON.dir/src/Bitboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/Bitboard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/Bitboard.cpp -o CMakeFiles/BRITON.dir/src/Bitboard.cpp.s

CMakeFiles/BRITON.dir/src/init.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/init.cpp.o: ../src/init.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/BRITON.dir/src/init.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/init.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/init.cpp

CMakeFiles/BRITON.dir/src/init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/init.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/init.cpp > CMakeFiles/BRITON.dir/src/init.cpp.i

CMakeFiles/BRITON.dir/src/init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/init.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/init.cpp -o CMakeFiles/BRITON.dir/src/init.cpp.s

CMakeFiles/BRITON.dir/src/movegen.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/movegen.cpp.o: ../src/movegen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/BRITON.dir/src/movegen.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/movegen.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/movegen.cpp

CMakeFiles/BRITON.dir/src/movegen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/movegen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/movegen.cpp > CMakeFiles/BRITON.dir/src/movegen.cpp.i

CMakeFiles/BRITON.dir/src/movegen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/movegen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/movegen.cpp -o CMakeFiles/BRITON.dir/src/movegen.cpp.s

CMakeFiles/BRITON.dir/src/bitops.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/bitops.cpp.o: ../src/bitops.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/BRITON.dir/src/bitops.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/bitops.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/bitops.cpp

CMakeFiles/BRITON.dir/src/bitops.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/bitops.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/bitops.cpp > CMakeFiles/BRITON.dir/src/bitops.cpp.i

CMakeFiles/BRITON.dir/src/bitops.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/bitops.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/bitops.cpp -o CMakeFiles/BRITON.dir/src/bitops.cpp.s

CMakeFiles/BRITON.dir/src/perft.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/perft.cpp.o: ../src/perft.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/BRITON.dir/src/perft.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/perft.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/perft.cpp

CMakeFiles/BRITON.dir/src/perft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/perft.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/perft.cpp > CMakeFiles/BRITON.dir/src/perft.cpp.i

CMakeFiles/BRITON.dir/src/perft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/perft.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/perft.cpp -o CMakeFiles/BRITON.dir/src/perft.cpp.s

CMakeFiles/BRITON.dir/src/eval.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/eval.cpp.o: ../src/eval.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/BRITON.dir/src/eval.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/eval.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/eval.cpp

CMakeFiles/BRITON.dir/src/eval.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/eval.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/eval.cpp > CMakeFiles/BRITON.dir/src/eval.cpp.i

CMakeFiles/BRITON.dir/src/eval.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/eval.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/eval.cpp -o CMakeFiles/BRITON.dir/src/eval.cpp.s

CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.o: ../src/TranspositionTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/TranspositionTable.cpp

CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/TranspositionTable.cpp > CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.i

CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/TranspositionTable.cpp -o CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.s

CMakeFiles/BRITON.dir/src/search.cpp.o: CMakeFiles/BRITON.dir/flags.make
CMakeFiles/BRITON.dir/src/search.cpp.o: ../src/search.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/BRITON.dir/src/search.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BRITON.dir/src/search.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/src/search.cpp

CMakeFiles/BRITON.dir/src/search.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BRITON.dir/src/search.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/src/search.cpp > CMakeFiles/BRITON.dir/src/search.cpp.i

CMakeFiles/BRITON.dir/src/search.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BRITON.dir/src/search.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/src/search.cpp -o CMakeFiles/BRITON.dir/src/search.cpp.s

# Object files for target BRITON
BRITON_OBJECTS = \
"CMakeFiles/BRITON.dir/src/main.cpp.o" \
"CMakeFiles/BRITON.dir/src/Position.cpp.o" \
"CMakeFiles/BRITON.dir/src/misc.cpp.o" \
"CMakeFiles/BRITON.dir/src/Bitboard.cpp.o" \
"CMakeFiles/BRITON.dir/src/init.cpp.o" \
"CMakeFiles/BRITON.dir/src/movegen.cpp.o" \
"CMakeFiles/BRITON.dir/src/bitops.cpp.o" \
"CMakeFiles/BRITON.dir/src/perft.cpp.o" \
"CMakeFiles/BRITON.dir/src/eval.cpp.o" \
"CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.o" \
"CMakeFiles/BRITON.dir/src/search.cpp.o"

# External object files for target BRITON
BRITON_EXTERNAL_OBJECTS =

BRITON: CMakeFiles/BRITON.dir/src/main.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/Position.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/misc.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/Bitboard.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/init.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/movegen.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/bitops.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/perft.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/eval.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/TranspositionTable.cpp.o
BRITON: CMakeFiles/BRITON.dir/src/search.cpp.o
BRITON: CMakeFiles/BRITON.dir/build.make
BRITON: CMakeFiles/BRITON.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable BRITON"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BRITON.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BRITON.dir/build: BRITON

.PHONY : CMakeFiles/BRITON.dir/build

CMakeFiles/BRITON.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BRITON.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BRITON.dir/clean

CMakeFiles/BRITON.dir/depend:
	cd /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brianton/Desktop/Chess-Engine-Cpp /home/brianton/Desktop/Chess-Engine-Cpp /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles/BRITON.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BRITON.dir/depend

