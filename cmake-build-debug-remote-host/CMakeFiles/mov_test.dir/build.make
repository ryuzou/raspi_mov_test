# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ryuzot/raspi_mov

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ryuzot/raspi_mov/cmake-build-debug-remote-host

# Include any dependencies generated for this target.
include CMakeFiles/mov_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mov_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mov_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mov_test.dir/flags.make

CMakeFiles/mov_test.dir/main.cpp.o: CMakeFiles/mov_test.dir/flags.make
CMakeFiles/mov_test.dir/main.cpp.o: ../main.cpp
CMakeFiles/mov_test.dir/main.cpp.o: CMakeFiles/mov_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ryuzot/raspi_mov/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mov_test.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mov_test.dir/main.cpp.o -MF CMakeFiles/mov_test.dir/main.cpp.o.d -o CMakeFiles/mov_test.dir/main.cpp.o -c /home/ryuzot/raspi_mov/main.cpp

CMakeFiles/mov_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mov_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ryuzot/raspi_mov/main.cpp > CMakeFiles/mov_test.dir/main.cpp.i

CMakeFiles/mov_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mov_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ryuzot/raspi_mov/main.cpp -o CMakeFiles/mov_test.dir/main.cpp.s

CMakeFiles/mov_test.dir/omni.cpp.o: CMakeFiles/mov_test.dir/flags.make
CMakeFiles/mov_test.dir/omni.cpp.o: ../omni.cpp
CMakeFiles/mov_test.dir/omni.cpp.o: CMakeFiles/mov_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ryuzot/raspi_mov/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mov_test.dir/omni.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mov_test.dir/omni.cpp.o -MF CMakeFiles/mov_test.dir/omni.cpp.o.d -o CMakeFiles/mov_test.dir/omni.cpp.o -c /home/ryuzot/raspi_mov/omni.cpp

CMakeFiles/mov_test.dir/omni.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mov_test.dir/omni.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ryuzot/raspi_mov/omni.cpp > CMakeFiles/mov_test.dir/omni.cpp.i

CMakeFiles/mov_test.dir/omni.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mov_test.dir/omni.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ryuzot/raspi_mov/omni.cpp -o CMakeFiles/mov_test.dir/omni.cpp.s

CMakeFiles/mov_test.dir/utils.cpp.o: CMakeFiles/mov_test.dir/flags.make
CMakeFiles/mov_test.dir/utils.cpp.o: ../utils.cpp
CMakeFiles/mov_test.dir/utils.cpp.o: CMakeFiles/mov_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ryuzot/raspi_mov/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mov_test.dir/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mov_test.dir/utils.cpp.o -MF CMakeFiles/mov_test.dir/utils.cpp.o.d -o CMakeFiles/mov_test.dir/utils.cpp.o -c /home/ryuzot/raspi_mov/utils.cpp

CMakeFiles/mov_test.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mov_test.dir/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ryuzot/raspi_mov/utils.cpp > CMakeFiles/mov_test.dir/utils.cpp.i

CMakeFiles/mov_test.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mov_test.dir/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ryuzot/raspi_mov/utils.cpp -o CMakeFiles/mov_test.dir/utils.cpp.s

# Object files for target mov_test
mov_test_OBJECTS = \
"CMakeFiles/mov_test.dir/main.cpp.o" \
"CMakeFiles/mov_test.dir/omni.cpp.o" \
"CMakeFiles/mov_test.dir/utils.cpp.o"

# External object files for target mov_test
mov_test_EXTERNAL_OBJECTS =

mov_test: CMakeFiles/mov_test.dir/main.cpp.o
mov_test: CMakeFiles/mov_test.dir/omni.cpp.o
mov_test: CMakeFiles/mov_test.dir/utils.cpp.o
mov_test: CMakeFiles/mov_test.dir/build.make
mov_test: CMakeFiles/mov_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ryuzot/raspi_mov/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mov_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mov_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mov_test.dir/build: mov_test
.PHONY : CMakeFiles/mov_test.dir/build

CMakeFiles/mov_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mov_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mov_test.dir/clean

CMakeFiles/mov_test.dir/depend:
	cd /home/ryuzot/raspi_mov/cmake-build-debug-remote-host && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ryuzot/raspi_mov /home/ryuzot/raspi_mov /home/ryuzot/raspi_mov/cmake-build-debug-remote-host /home/ryuzot/raspi_mov/cmake-build-debug-remote-host /home/ryuzot/raspi_mov/cmake-build-debug-remote-host/CMakeFiles/mov_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mov_test.dir/depend

