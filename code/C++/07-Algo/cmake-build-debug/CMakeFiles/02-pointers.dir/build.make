# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Apps\CLion 2022.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Apps\CLion 2022.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/02-pointers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/02-pointers.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/02-pointers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/02-pointers.dir/flags.make

CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.obj: CMakeFiles/02-pointers.dir/flags.make
CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.obj: D:/GitHub-repos/sunc4127.github.io/code/C++/07-Algo/src/000-Ultimate-C++-Part2/02-pointers.cpp
CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.obj: CMakeFiles/02-pointers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.obj"
	"D:\Apps\CLion 2022.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.obj -MF CMakeFiles\02-pointers.dir\src\000-Ultimate-C++-Part2\02-pointers.cpp.obj.d -o CMakeFiles\02-pointers.dir\src\000-Ultimate-C++-Part2\02-pointers.cpp.obj -c D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\src\000-Ultimate-C++-Part2\02-pointers.cpp

CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.i"
	"D:\Apps\CLion 2022.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\src\000-Ultimate-C++-Part2\02-pointers.cpp > CMakeFiles\02-pointers.dir\src\000-Ultimate-C++-Part2\02-pointers.cpp.i

CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.s"
	"D:\Apps\CLion 2022.3\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\src\000-Ultimate-C++-Part2\02-pointers.cpp -o CMakeFiles\02-pointers.dir\src\000-Ultimate-C++-Part2\02-pointers.cpp.s

# Object files for target 02-pointers
02__pointers_OBJECTS = \
"CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.obj"

# External object files for target 02-pointers
02__pointers_EXTERNAL_OBJECTS =

02-pointers.exe: CMakeFiles/02-pointers.dir/src/000-Ultimate-C++-Part2/02-pointers.cpp.obj
02-pointers.exe: CMakeFiles/02-pointers.dir/build.make
02-pointers.exe: CMakeFiles/02-pointers.dir/linkLibs.rsp
02-pointers.exe: CMakeFiles/02-pointers.dir/objects1.rsp
02-pointers.exe: CMakeFiles/02-pointers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 02-pointers.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\02-pointers.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/02-pointers.dir/build: 02-pointers.exe
.PHONY : CMakeFiles/02-pointers.dir/build

CMakeFiles/02-pointers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\02-pointers.dir\cmake_clean.cmake
.PHONY : CMakeFiles/02-pointers.dir/clean

CMakeFiles/02-pointers.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\cmake-build-debug D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\cmake-build-debug D:\GitHub-repos\sunc4127.github.io\code\C++\07-Algo\cmake-build-debug\CMakeFiles\02-pointers.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/02-pointers.dir/depend

