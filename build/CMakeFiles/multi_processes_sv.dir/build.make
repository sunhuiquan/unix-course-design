# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/february/work/exercise/unix-course-design

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/february/work/exercise/unix-course-design/build

# Include any dependencies generated for this target.
include CMakeFiles/multi_processes_sv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multi_processes_sv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multi_processes_sv.dir/flags.make

CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.o: CMakeFiles/multi_processes_sv.dir/flags.make
CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.o: ../src/multi_processes_sv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/february/work/exercise/unix-course-design/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.o   -c /home/february/work/exercise/unix-course-design/src/multi_processes_sv.c

CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/february/work/exercise/unix-course-design/src/multi_processes_sv.c > CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.i

CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/february/work/exercise/unix-course-design/src/multi_processes_sv.c -o CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.s

CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.o: CMakeFiles/multi_processes_sv.dir/flags.make
CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.o: ../src/inet_sockets.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/february/work/exercise/unix-course-design/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.o   -c /home/february/work/exercise/unix-course-design/src/inet_sockets.c

CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/february/work/exercise/unix-course-design/src/inet_sockets.c > CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.i

CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/february/work/exercise/unix-course-design/src/inet_sockets.c -o CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.s

# Object files for target multi_processes_sv
multi_processes_sv_OBJECTS = \
"CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.o" \
"CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.o"

# External object files for target multi_processes_sv
multi_processes_sv_EXTERNAL_OBJECTS =

multi_processes_sv: CMakeFiles/multi_processes_sv.dir/src/multi_processes_sv.c.o
multi_processes_sv: CMakeFiles/multi_processes_sv.dir/src/inet_sockets.c.o
multi_processes_sv: CMakeFiles/multi_processes_sv.dir/build.make
multi_processes_sv: CMakeFiles/multi_processes_sv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/february/work/exercise/unix-course-design/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable multi_processes_sv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multi_processes_sv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multi_processes_sv.dir/build: multi_processes_sv

.PHONY : CMakeFiles/multi_processes_sv.dir/build

CMakeFiles/multi_processes_sv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multi_processes_sv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multi_processes_sv.dir/clean

CMakeFiles/multi_processes_sv.dir/depend:
	cd /home/february/work/exercise/unix-course-design/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/february/work/exercise/unix-course-design /home/february/work/exercise/unix-course-design /home/february/work/exercise/unix-course-design/build /home/february/work/exercise/unix-course-design/build /home/february/work/exercise/unix-course-design/build/CMakeFiles/multi_processes_sv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multi_processes_sv.dir/depend
