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
CMAKE_SOURCE_DIR = /home/das89/prog/CDLinkedList

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/das89/prog/CDLinkedList/build

# Include any dependencies generated for this target.
include CMakeFiles/CDLinkedList.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CDLinkedList.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CDLinkedList.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CDLinkedList.dir/flags.make

CMakeFiles/CDLinkedList.dir/test.cpp.o: CMakeFiles/CDLinkedList.dir/flags.make
CMakeFiles/CDLinkedList.dir/test.cpp.o: ../test.cpp
CMakeFiles/CDLinkedList.dir/test.cpp.o: CMakeFiles/CDLinkedList.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/das89/prog/CDLinkedList/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CDLinkedList.dir/test.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CDLinkedList.dir/test.cpp.o -MF CMakeFiles/CDLinkedList.dir/test.cpp.o.d -o CMakeFiles/CDLinkedList.dir/test.cpp.o -c /home/das89/prog/CDLinkedList/test.cpp

CMakeFiles/CDLinkedList.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CDLinkedList.dir/test.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/das89/prog/CDLinkedList/test.cpp > CMakeFiles/CDLinkedList.dir/test.cpp.i

CMakeFiles/CDLinkedList.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CDLinkedList.dir/test.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/das89/prog/CDLinkedList/test.cpp -o CMakeFiles/CDLinkedList.dir/test.cpp.s

# Object files for target CDLinkedList
CDLinkedList_OBJECTS = \
"CMakeFiles/CDLinkedList.dir/test.cpp.o"

# External object files for target CDLinkedList
CDLinkedList_EXTERNAL_OBJECTS =

libCDLinkedList.a: CMakeFiles/CDLinkedList.dir/test.cpp.o
libCDLinkedList.a: CMakeFiles/CDLinkedList.dir/build.make
libCDLinkedList.a: CMakeFiles/CDLinkedList.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/das89/prog/CDLinkedList/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCDLinkedList.a"
	$(CMAKE_COMMAND) -P CMakeFiles/CDLinkedList.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CDLinkedList.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CDLinkedList.dir/build: libCDLinkedList.a
.PHONY : CMakeFiles/CDLinkedList.dir/build

CMakeFiles/CDLinkedList.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CDLinkedList.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CDLinkedList.dir/clean

CMakeFiles/CDLinkedList.dir/depend:
	cd /home/das89/prog/CDLinkedList/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/das89/prog/CDLinkedList /home/das89/prog/CDLinkedList /home/das89/prog/CDLinkedList/build /home/das89/prog/CDLinkedList/build /home/das89/prog/CDLinkedList/build/CMakeFiles/CDLinkedList.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CDLinkedList.dir/depend

