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
include seg-apps/CMakeFiles/seg_LoAd.dir/depend.make

# Include the progress variables for this target.
include seg-apps/CMakeFiles/seg_LoAd.dir/progress.make

# Include the compile flags for this target's objects.
include seg-apps/CMakeFiles/seg_LoAd.dir/flags.make

seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o: seg-apps/CMakeFiles/seg_LoAd.dir/flags.make
seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o: source/seg-apps/seg_LoAd.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fati/Downloads/niftyseg/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o"
	cd /home/fati/Downloads/niftyseg/build/seg-apps && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o -c /home/fati/Downloads/niftyseg/build/source/seg-apps/seg_LoAd.cpp

seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.i"
	cd /home/fati/Downloads/niftyseg/build/seg-apps && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fati/Downloads/niftyseg/build/source/seg-apps/seg_LoAd.cpp > CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.i

seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.s"
	cd /home/fati/Downloads/niftyseg/build/seg-apps && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fati/Downloads/niftyseg/build/source/seg-apps/seg_LoAd.cpp -o CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.s

seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.requires:
.PHONY : seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.requires

seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.provides: seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.requires
	$(MAKE) -f seg-apps/CMakeFiles/seg_LoAd.dir/build.make seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.provides.build
.PHONY : seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.provides

seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.provides.build: seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o

# Object files for target seg_LoAd
seg_LoAd_OBJECTS = \
"CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o"

# External object files for target seg_LoAd
seg_LoAd_EXTERNAL_OBJECTS =

seg-apps/seg_LoAd: seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o
seg-apps/seg_LoAd: seg-apps/CMakeFiles/seg_LoAd.dir/build.make
seg-apps/seg_LoAd: seg-lib/lib_seg_LoAd.a
seg-apps/seg_LoAd: seg-lib/lib_seg_tools.a
seg-apps/seg_LoAd: seg-lib/lib_seg_MRF.a
seg-apps/seg_LoAd: seg-lib/lib_seg_FMM.a
seg-apps/seg_LoAd: seg-lib/lib_seg_BiasCorrection.a
seg-apps/seg_LoAd: nifti/lib_seg_nifti.a
seg-apps/seg_LoAd: zlib/libz.a
seg-apps/seg_LoAd: seg-lib/lib_seg_Topo.a
seg-apps/seg_LoAd: seg-apps/CMakeFiles/seg_LoAd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable seg_LoAd"
	cd /home/fati/Downloads/niftyseg/build/seg-apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/seg_LoAd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
seg-apps/CMakeFiles/seg_LoAd.dir/build: seg-apps/seg_LoAd
.PHONY : seg-apps/CMakeFiles/seg_LoAd.dir/build

seg-apps/CMakeFiles/seg_LoAd.dir/requires: seg-apps/CMakeFiles/seg_LoAd.dir/seg_LoAd.cpp.o.requires
.PHONY : seg-apps/CMakeFiles/seg_LoAd.dir/requires

seg-apps/CMakeFiles/seg_LoAd.dir/clean:
	cd /home/fati/Downloads/niftyseg/build/seg-apps && $(CMAKE_COMMAND) -P CMakeFiles/seg_LoAd.dir/cmake_clean.cmake
.PHONY : seg-apps/CMakeFiles/seg_LoAd.dir/clean

seg-apps/CMakeFiles/seg_LoAd.dir/depend:
	cd /home/fati/Downloads/niftyseg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fati/Downloads/niftyseg/build/source /home/fati/Downloads/niftyseg/build/source/seg-apps /home/fati/Downloads/niftyseg/build /home/fati/Downloads/niftyseg/build/seg-apps /home/fati/Downloads/niftyseg/build/seg-apps/CMakeFiles/seg_LoAd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : seg-apps/CMakeFiles/seg_LoAd.dir/depend

