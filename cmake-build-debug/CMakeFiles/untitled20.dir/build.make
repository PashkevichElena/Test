# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "/cygdrive/c/Users/Alena Pashkevich/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe"

# The command to remove a file.
RM = "/cygdrive/c/Users/Alena Pashkevich/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/untitled20.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled20.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled20.dir/flags.make

CMakeFiles/untitled20.dir/main.c.o: CMakeFiles/untitled20.dir/flags.make
CMakeFiles/untitled20.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/untitled20.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/untitled20.dir/main.c.o   -c "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/main.c"

CMakeFiles/untitled20.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/untitled20.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/main.c" > CMakeFiles/untitled20.dir/main.c.i

CMakeFiles/untitled20.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/untitled20.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/main.c" -o CMakeFiles/untitled20.dir/main.c.s

# Object files for target untitled20
untitled20_OBJECTS = \
"CMakeFiles/untitled20.dir/main.c.o"

# External object files for target untitled20
untitled20_EXTERNAL_OBJECTS =

untitled20.exe: CMakeFiles/untitled20.dir/main.c.o
untitled20.exe: CMakeFiles/untitled20.dir/build.make
untitled20.exe: CMakeFiles/untitled20.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable untitled20.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled20.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled20.dir/build: untitled20.exe

.PHONY : CMakeFiles/untitled20.dir/build

CMakeFiles/untitled20.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled20.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled20.dir/clean

CMakeFiles/untitled20.dir/depend:
	cd "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20" "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20" "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/cmake-build-debug" "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/cmake-build-debug" "/cygdrive/c/Users/Alena Pashkevich/CLionProjects/untitled20/cmake-build-debug/CMakeFiles/untitled20.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/untitled20.dir/depend
