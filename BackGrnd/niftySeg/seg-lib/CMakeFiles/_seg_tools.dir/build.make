# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fati/Downloads/niftyseg/build/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fati/Downloads/niftyseg/build

# Include any dependencies generated for this target.
include seg-lib/CMakeFiles/_seg_tools.dir/depend.make

# Include the progress variables for this target.
include seg-lib/CMakeFiles/_seg_tools.dir/progress.make

# Include the compile flags for this target's objects.
include seg-lib/CMakeFiles/_seg_tools.dir/flags.make

seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o: seg-lib/CMakeFiles/_seg_tools.dir/flags.make
seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o: source/seg-lib/_seg_tools.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fati/Downloads/niftyseg/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o"
	cd /home/fati/Downloads/niftyseg/build/seg-lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o -c /home/fati/Downloads/niftyseg/build/source/seg-lib/_seg_tools.cpp

seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_seg_tools.dir/_seg_tools.cpp.i"
	cd /home/fati/Downloads/niftyseg/build/seg-lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fati/Downloads/niftyseg/build/source/seg-lib/_seg_tools.cpp > CMakeFiles/_seg_tools.dir/_seg_tools.cpp.i

seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_seg_tools.dir/_seg_tools.cpp.s"
	cd /home/fati/Downloads/niftyseg/build/seg-lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fati/Downloads/niftyseg/build/source/seg-lib/_seg_tools.cpp -o CMakeFiles/_seg_tools.dir/_seg_tools.cpp.s

seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.requires:
.PHONY : seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.requires

seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.provides: seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.requires
	$(MAKE) -f seg-lib/CMakeFiles/_seg_tools.dir/build.make seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.provides.build
.PHONY : seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.provides

seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.provides.build: seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o

# Object files for target _seg_tools
_seg_tools_OBJECTS = \
"CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o"

# External object files for target _seg_tools
_seg_tools_EXTERNAL_OBJECTS =

seg-lib/lib_seg_tools.a: seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o
seg-lib/lib_seg_tools.a: seg-lib/CMakeFiles/_seg_tools.dir/build.make
seg-lib/lib_seg_tools.a: seg-lib/CMakeFiles/_seg_tools.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library lib_seg_tools.a"
	cd /home/fati/Downloads/niftyseg/build/seg-lib && $(CMAKE_COMMAND) -P CMakeFiles/_seg_tools.dir/cmake_clean_target.cmake
	cd /home/fati/Downloads/niftyseg/build/seg-lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_seg_tools.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
seg-lib/CMakeFiles/_seg_tools.dir/build: seg-lib/lib_seg_tools.a
.PHONY : seg-lib/CMakeFiles/_seg_tools.dir/build

seg-lib/CMakeFiles/_seg_tools.dir/requires: seg-lib/CMakeFiles/_seg_tools.dir/_seg_tools.cpp.o.requires
.PHONY : seg-lib/CMakeFiles/_seg_tools.dir/requires

seg-lib/CMakeFiles/_seg_tools.dir/clean:
	cd /home/fati/Downloads/niftyseg/build/seg-lib && $(CMAKE_COMMAND) -P CMakeFiles/_seg_tools.dir/cmake_clean.cmake
.PHONY : seg-lib/CMakeFiles/_seg_tools.dir/clean

seg-lib/CMakeFiles/_seg_tools.dir/depend:
	cd /home/fati/Downloads/niftyseg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fati/Downloads/niftyseg/build/source /home/fati/Downloads/niftyseg/build/source/seg-lib /home/fati/Downloads/niftyseg/build /home/fati/Downloads/niftyseg/build/seg-lib /home/fati/Downloads/niftyseg/build/seg-lib/CMakeFiles/_seg_tools.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : seg-lib/CMakeFiles/_seg_tools.dir/depend

