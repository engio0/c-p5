# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.11

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\ProgramFiles\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\ProgramFiles\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Dev\primer\wxWidgets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Dev\primer\wxWidgets

# Include any dependencies generated for this target.
include CMakeFiles/wxWidgetsTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wxWidgetsTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wxWidgetsTest.dir/flags.make

CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.obj: CMakeFiles/wxWidgetsTest.dir/flags.make
CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.obj: CMakeFiles/wxWidgetsTest.dir/includes_CXX.rsp
CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.obj: HelloWorldApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Dev\primer\wxWidgets\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.obj"
	D:\ProgramFiles\MinGW-W64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\wxWidgetsTest.dir\HelloWorldApp.cpp.obj -c D:\Dev\primer\wxWidgets\HelloWorldApp.cpp

CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.i"
	D:\ProgramFiles\MinGW-W64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Dev\primer\wxWidgets\HelloWorldApp.cpp > CMakeFiles\wxWidgetsTest.dir\HelloWorldApp.cpp.i

CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.s"
	D:\ProgramFiles\MinGW-W64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Dev\primer\wxWidgets\HelloWorldApp.cpp -o CMakeFiles\wxWidgetsTest.dir\HelloWorldApp.cpp.s

# Object files for target wxWidgetsTest
wxWidgetsTest_OBJECTS = \
"CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.obj"

# External object files for target wxWidgetsTest
wxWidgetsTest_EXTERNAL_OBJECTS =

wxWidgetsTest.exe: CMakeFiles/wxWidgetsTest.dir/HelloWorldApp.cpp.obj
wxWidgetsTest.exe: CMakeFiles/wxWidgetsTest.dir/build.make
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libSDL2main.a
wxWidgetsTest.exe: C:/Windows/System32/SDL2.dll
wxWidgetsTest.exe: C:/Windows/System32/SDL2_image.dll
wxWidgetsTest.exe: C:/Windows/System32/SDL2_ttf.dll
wxWidgetsTest.exe: C:/Windows/System32/SDL2_mixer.dll
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxmsw31u_core.a
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxbase31u.a
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxpng.a
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxtiff.a
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxjpeg.a
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxzlib.a
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxregexu.a
wxWidgetsTest.exe: D:/usr/x86_64-w64-mingw32/lib/libwxexpat.a
wxWidgetsTest.exe: CMakeFiles/wxWidgetsTest.dir/linklibs.rsp
wxWidgetsTest.exe: CMakeFiles/wxWidgetsTest.dir/objects1.rsp
wxWidgetsTest.exe: CMakeFiles/wxWidgetsTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Dev\primer\wxWidgets\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wxWidgetsTest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\wxWidgetsTest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wxWidgetsTest.dir/build: wxWidgetsTest.exe

.PHONY : CMakeFiles/wxWidgetsTest.dir/build

CMakeFiles/wxWidgetsTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\wxWidgetsTest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/wxWidgetsTest.dir/clean

CMakeFiles/wxWidgetsTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Dev\primer\wxWidgets D:\Dev\primer\wxWidgets D:\Dev\primer\wxWidgets D:\Dev\primer\wxWidgets D:\Dev\primer\wxWidgets\CMakeFiles\wxWidgetsTest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wxWidgetsTest.dir/depend

