# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/lvx/Projects/Aulas/AED/aed-schedules

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lvx/Projects/Aulas/AED/aed-schedules

# Utility rule file for Doxygen.

# Include any custom commands dependencies for this target.
include CMakeFiles/Doxygen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Doxygen.dir/progress.make

CMakeFiles/Doxygen:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/lvx/Projects/Aulas/AED/aed-schedules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating API documentation with Doxygen"
	/usr/bin/doxygen /home/lvx/Projects/Aulas/AED/aed-schedules/Doxyfile

Doxygen: CMakeFiles/Doxygen
Doxygen: CMakeFiles/Doxygen.dir/build.make
.PHONY : Doxygen

# Rule to build all files generated by this target.
CMakeFiles/Doxygen.dir/build: Doxygen
.PHONY : CMakeFiles/Doxygen.dir/build

CMakeFiles/Doxygen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Doxygen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Doxygen.dir/clean

CMakeFiles/Doxygen.dir/depend:
	cd /home/lvx/Projects/Aulas/AED/aed-schedules && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lvx/Projects/Aulas/AED/aed-schedules /home/lvx/Projects/Aulas/AED/aed-schedules /home/lvx/Projects/Aulas/AED/aed-schedules /home/lvx/Projects/Aulas/AED/aed-schedules /home/lvx/Projects/Aulas/AED/aed-schedules/CMakeFiles/Doxygen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Doxygen.dir/depend

