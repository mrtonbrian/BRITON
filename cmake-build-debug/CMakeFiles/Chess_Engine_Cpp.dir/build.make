# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/73/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/73/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brianton/Desktop/Chess-Engine-Cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Chess_Engine_Cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Chess_Engine_Cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chess_Engine_Cpp.dir/flags.make

CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.o: ../attack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/attack.cpp

CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/attack.cpp > CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/attack.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.o: ../bitboards.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/bitboards.cpp

CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/bitboards.cpp > CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/bitboards.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.o: ../board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/board.cpp

CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/board.cpp > CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/board.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.o: ../evaluate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/evaluate.cpp

CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/evaluate.cpp > CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/evaluate.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.o: ../hashkey.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/hashkey.cpp

CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/hashkey.cpp > CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/hashkey.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.o: ../init.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/init.cpp

CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/init.cpp > CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/init.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.o: ../io.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/io.cpp

CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/io.cpp > CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/io.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/main.cpp

CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/main.cpp > CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/main.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.o: ../makemove.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/makemove.cpp

CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/makemove.cpp > CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/makemove.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.o: ../misc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/misc.cpp

CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/misc.cpp > CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/misc.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.o: ../move.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/move.cpp

CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/move.cpp > CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/move.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.o: ../movegen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/movegen.cpp

CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/movegen.cpp > CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/movegen.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.o: ../perft.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/perft.cpp

CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/perft.cpp > CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/perft.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.o: ../pvtable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/pvtable.cpp

CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/pvtable.cpp > CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/pvtable.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.o: ../search.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/search.cpp

CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/search.cpp > CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/search.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.o: ../uci.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/uci.cpp

CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/uci.cpp > CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/uci.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.s

CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.o: CMakeFiles/Chess_Engine_Cpp.dir/flags.make
CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.o: ../validate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.o -c /home/brianton/Desktop/Chess-Engine-Cpp/validate.cpp

CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brianton/Desktop/Chess-Engine-Cpp/validate.cpp > CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.i

CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brianton/Desktop/Chess-Engine-Cpp/validate.cpp -o CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.s

# Object files for target Chess_Engine_Cpp
Chess_Engine_Cpp_OBJECTS = \
"CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.o" \
"CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.o"

# External object files for target Chess_Engine_Cpp
Chess_Engine_Cpp_EXTERNAL_OBJECTS =

Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/attack.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/bitboards.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/board.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/evaluate.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/hashkey.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/init.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/io.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/main.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/makemove.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/misc.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/move.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/movegen.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/perft.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/pvtable.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/search.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/uci.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/validate.cpp.o
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/build.make
Chess_Engine_Cpp: CMakeFiles/Chess_Engine_Cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable Chess_Engine_Cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chess_Engine_Cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chess_Engine_Cpp.dir/build: Chess_Engine_Cpp

.PHONY : CMakeFiles/Chess_Engine_Cpp.dir/build

CMakeFiles/Chess_Engine_Cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Chess_Engine_Cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Chess_Engine_Cpp.dir/clean

CMakeFiles/Chess_Engine_Cpp.dir/depend:
	cd /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brianton/Desktop/Chess-Engine-Cpp /home/brianton/Desktop/Chess-Engine-Cpp /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug /home/brianton/Desktop/Chess-Engine-Cpp/cmake-build-debug/CMakeFiles/Chess_Engine_Cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Chess_Engine_Cpp.dir/depend
