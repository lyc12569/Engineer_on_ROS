# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adminpc/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adminpc/catkin_ws/src/build

# Utility rule file for depthai_ros_driver_gencfg.

# Include any custom commands dependencies for this target.
include sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/compiler_depend.make

# Include the progress variables for this target.
include sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/progress.make

sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg: devel/include/depthai_ros_driver/parametersConfig.h
sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg: devel/lib/python3/dist-packages/depthai_ros_driver/cfg/parametersConfig.py

devel/include/depthai_ros_driver/parametersConfig.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_driver/cfg/parameters.cfg
devel/include/depthai_ros_driver/parametersConfig.h: /opt/ros/noetic/share/dynamic_reconfigure/templates/ConfigType.py.template
devel/include/depthai_ros_driver/parametersConfig.h: /opt/ros/noetic/share/dynamic_reconfigure/templates/ConfigType.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating dynamic reconfigure files from cfg/parameters.cfg: /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_driver/parametersConfig.h /home/adminpc/catkin_ws/src/build/devel/lib/python3/dist-packages/depthai_ros_driver/cfg/parametersConfig.py"
	cd /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_driver && ../../../catkin_generated/env_cached.sh /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_driver/setup_custom_pythonpath.sh /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_driver/cfg/parameters.cfg /opt/ros/noetic/share/dynamic_reconfigure/cmake/.. /home/adminpc/catkin_ws/src/build/devel/share/depthai_ros_driver /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_driver /home/adminpc/catkin_ws/src/build/devel/lib/python3/dist-packages/depthai_ros_driver

devel/share/depthai_ros_driver/docs/parametersConfig.dox: devel/include/depthai_ros_driver/parametersConfig.h
	@$(CMAKE_COMMAND) -E touch_nocreate devel/share/depthai_ros_driver/docs/parametersConfig.dox

devel/share/depthai_ros_driver/docs/parametersConfig-usage.dox: devel/include/depthai_ros_driver/parametersConfig.h
	@$(CMAKE_COMMAND) -E touch_nocreate devel/share/depthai_ros_driver/docs/parametersConfig-usage.dox

devel/lib/python3/dist-packages/depthai_ros_driver/cfg/parametersConfig.py: devel/include/depthai_ros_driver/parametersConfig.h
	@$(CMAKE_COMMAND) -E touch_nocreate devel/lib/python3/dist-packages/depthai_ros_driver/cfg/parametersConfig.py

devel/share/depthai_ros_driver/docs/parametersConfig.wikidoc: devel/include/depthai_ros_driver/parametersConfig.h
	@$(CMAKE_COMMAND) -E touch_nocreate devel/share/depthai_ros_driver/docs/parametersConfig.wikidoc

depthai_ros_driver_gencfg: devel/include/depthai_ros_driver/parametersConfig.h
depthai_ros_driver_gencfg: devel/lib/python3/dist-packages/depthai_ros_driver/cfg/parametersConfig.py
depthai_ros_driver_gencfg: devel/share/depthai_ros_driver/docs/parametersConfig-usage.dox
depthai_ros_driver_gencfg: devel/share/depthai_ros_driver/docs/parametersConfig.dox
depthai_ros_driver_gencfg: devel/share/depthai_ros_driver/docs/parametersConfig.wikidoc
depthai_ros_driver_gencfg: sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg
depthai_ros_driver_gencfg: sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/build.make
.PHONY : depthai_ros_driver_gencfg

# Rule to build all files generated by this target.
sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/build: depthai_ros_driver_gencfg
.PHONY : sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/build

sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/clean:
	cd /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_driver && $(CMAKE_COMMAND) -P CMakeFiles/depthai_ros_driver_gencfg.dir/cmake_clean.cmake
.PHONY : sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/clean

sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/depend:
	cd /home/adminpc/catkin_ws/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adminpc/catkin_ws/src /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_driver /home/adminpc/catkin_ws/src/build /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_driver /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sp_vision/depthai-ros/depthai_ros_driver/CMakeFiles/depthai_ros_driver_gencfg.dir/depend
