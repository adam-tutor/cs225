# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/bin/cmake3

# The command to remove a file.
RM = /usr/bin/cmake3 -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tutor2/cs225git/mp_schedule

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tutor2/cs225git/mp_schedule/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/cs225.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/cs225.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/cs225.dir/flags.make

lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o: lib/CMakeFiles/cs225.dir/flags.make
lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o: ../lib/cs225/HSLAPixel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tutor2/cs225git/mp_schedule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o"
	cd /home/tutor2/cs225git/mp_schedule/build/lib && /software/llvm-6.0.1/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o -c /home/tutor2/cs225git/mp_schedule/lib/cs225/HSLAPixel.cpp

lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.i"
	cd /home/tutor2/cs225git/mp_schedule/build/lib && /software/llvm-6.0.1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tutor2/cs225git/mp_schedule/lib/cs225/HSLAPixel.cpp > CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.i

lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.s"
	cd /home/tutor2/cs225git/mp_schedule/build/lib && /software/llvm-6.0.1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tutor2/cs225git/mp_schedule/lib/cs225/HSLAPixel.cpp -o CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.s

lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o: lib/CMakeFiles/cs225.dir/flags.make
lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o: ../lib/cs225/PNG.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tutor2/cs225git/mp_schedule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o"
	cd /home/tutor2/cs225git/mp_schedule/build/lib && /software/llvm-6.0.1/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cs225.dir/cs225/PNG.cpp.o -c /home/tutor2/cs225git/mp_schedule/lib/cs225/PNG.cpp

lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs225.dir/cs225/PNG.cpp.i"
	cd /home/tutor2/cs225git/mp_schedule/build/lib && /software/llvm-6.0.1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tutor2/cs225git/mp_schedule/lib/cs225/PNG.cpp > CMakeFiles/cs225.dir/cs225/PNG.cpp.i

lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs225.dir/cs225/PNG.cpp.s"
	cd /home/tutor2/cs225git/mp_schedule/build/lib && /software/llvm-6.0.1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tutor2/cs225git/mp_schedule/lib/cs225/PNG.cpp -o CMakeFiles/cs225.dir/cs225/PNG.cpp.s

# Object files for target cs225
cs225_OBJECTS = \
"CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o" \
"CMakeFiles/cs225.dir/cs225/PNG.cpp.o"

# External object files for target cs225
cs225_EXTERNAL_OBJECTS =

lib/libcs225.a: lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o
lib/libcs225.a: lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o
lib/libcs225.a: lib/CMakeFiles/cs225.dir/build.make
lib/libcs225.a: lib/CMakeFiles/cs225.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tutor2/cs225git/mp_schedule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcs225.a"
	cd /home/tutor2/cs225git/mp_schedule/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/cs225.dir/cmake_clean_target.cmake
	cd /home/tutor2/cs225git/mp_schedule/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cs225.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/cs225.dir/build: lib/libcs225.a

.PHONY : lib/CMakeFiles/cs225.dir/build

lib/CMakeFiles/cs225.dir/clean:
	cd /home/tutor2/cs225git/mp_schedule/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/cs225.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/cs225.dir/clean

lib/CMakeFiles/cs225.dir/depend:
	cd /home/tutor2/cs225git/mp_schedule/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tutor2/cs225git/mp_schedule /home/tutor2/cs225git/mp_schedule/lib /home/tutor2/cs225git/mp_schedule/build /home/tutor2/cs225git/mp_schedule/build/lib /home/tutor2/cs225git/mp_schedule/build/lib/CMakeFiles/cs225.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/cs225.dir/depend

