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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HalfPlaneSquare.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HalfPlaneSquare.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HalfPlaneSquare.dir/flags.make

CMakeFiles/HalfPlaneSquare.dir/main.cpp.o: CMakeFiles/HalfPlaneSquare.dir/flags.make
CMakeFiles/HalfPlaneSquare.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HalfPlaneSquare.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HalfPlaneSquare.dir/main.cpp.o -c /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/main.cpp

CMakeFiles/HalfPlaneSquare.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HalfPlaneSquare.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/main.cpp > CMakeFiles/HalfPlaneSquare.dir/main.cpp.i

CMakeFiles/HalfPlaneSquare.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HalfPlaneSquare.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/main.cpp -o CMakeFiles/HalfPlaneSquare.dir/main.cpp.s

# Object files for target HalfPlaneSquare
HalfPlaneSquare_OBJECTS = \
"CMakeFiles/HalfPlaneSquare.dir/main.cpp.o"

# External object files for target HalfPlaneSquare
HalfPlaneSquare_EXTERNAL_OBJECTS =

HalfPlaneSquare: CMakeFiles/HalfPlaneSquare.dir/main.cpp.o
HalfPlaneSquare: CMakeFiles/HalfPlaneSquare.dir/build.make
HalfPlaneSquare: CMakeFiles/HalfPlaneSquare.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HalfPlaneSquare"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HalfPlaneSquare.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HalfPlaneSquare.dir/build: HalfPlaneSquare

.PHONY : CMakeFiles/HalfPlaneSquare.dir/build

CMakeFiles/HalfPlaneSquare.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HalfPlaneSquare.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HalfPlaneSquare.dir/clean

CMakeFiles/HalfPlaneSquare.dir/depend:
	cd /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/cmake-build-debug /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/cmake-build-debug /Users/Stephan/CLionProjects/ComputationalGeometry/HalfPlaneSquare/cmake-build-debug/CMakeFiles/HalfPlaneSquare.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HalfPlaneSquare.dir/depend
