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
CMAKE_COMMAND = /home/pan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/pan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pan/CLionProjects/RuralCV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pan/CLionProjects/RuralCV/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RuralCV.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RuralCV.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RuralCV.dir/flags.make

CMakeFiles/RuralCV.dir/main.cpp.o: CMakeFiles/RuralCV.dir/flags.make
CMakeFiles/RuralCV.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pan/CLionProjects/RuralCV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RuralCV.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RuralCV.dir/main.cpp.o -c /home/pan/CLionProjects/RuralCV/main.cpp

CMakeFiles/RuralCV.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RuralCV.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pan/CLionProjects/RuralCV/main.cpp > CMakeFiles/RuralCV.dir/main.cpp.i

CMakeFiles/RuralCV.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RuralCV.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pan/CLionProjects/RuralCV/main.cpp -o CMakeFiles/RuralCV.dir/main.cpp.s

# Object files for target RuralCV
RuralCV_OBJECTS = \
"CMakeFiles/RuralCV.dir/main.cpp.o"

# External object files for target RuralCV
RuralCV_EXTERNAL_OBJECTS =

RuralCV: CMakeFiles/RuralCV.dir/main.cpp.o
RuralCV: CMakeFiles/RuralCV.dir/build.make
RuralCV: /usr/local/lib/libopencv_dnn.so.3.4.11
RuralCV: /usr/local/lib/libopencv_highgui.so.3.4.11
RuralCV: /usr/local/lib/libopencv_ml.so.3.4.11
RuralCV: /usr/local/lib/libopencv_objdetect.so.3.4.11
RuralCV: /usr/local/lib/libopencv_shape.so.3.4.11
RuralCV: /usr/local/lib/libopencv_stitching.so.3.4.11
RuralCV: /usr/local/lib/libopencv_superres.so.3.4.11
RuralCV: /usr/local/lib/libopencv_videostab.so.3.4.11
RuralCV: /usr/local/lib/libopencv_calib3d.so.3.4.11
RuralCV: /usr/local/lib/libopencv_features2d.so.3.4.11
RuralCV: /usr/local/lib/libopencv_flann.so.3.4.11
RuralCV: /usr/local/lib/libopencv_photo.so.3.4.11
RuralCV: /usr/local/lib/libopencv_video.so.3.4.11
RuralCV: /usr/local/lib/libopencv_videoio.so.3.4.11
RuralCV: /usr/local/lib/libopencv_imgcodecs.so.3.4.11
RuralCV: /usr/local/lib/libopencv_imgproc.so.3.4.11
RuralCV: /usr/local/lib/libopencv_core.so.3.4.11
RuralCV: CMakeFiles/RuralCV.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pan/CLionProjects/RuralCV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RuralCV"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RuralCV.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RuralCV.dir/build: RuralCV

.PHONY : CMakeFiles/RuralCV.dir/build

CMakeFiles/RuralCV.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RuralCV.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RuralCV.dir/clean

CMakeFiles/RuralCV.dir/depend:
	cd /home/pan/CLionProjects/RuralCV/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pan/CLionProjects/RuralCV /home/pan/CLionProjects/RuralCV /home/pan/CLionProjects/RuralCV/cmake-build-debug /home/pan/CLionProjects/RuralCV/cmake-build-debug /home/pan/CLionProjects/RuralCV/cmake-build-debug/CMakeFiles/RuralCV.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RuralCV.dir/depend

