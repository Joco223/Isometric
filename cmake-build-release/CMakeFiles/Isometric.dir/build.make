# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\programming\cpp\Isometric

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\programming\cpp\Isometric\cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/Isometric.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Isometric.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Isometric.dir/flags.make

CMakeFiles/Isometric.dir/source/main.cpp.obj: CMakeFiles/Isometric.dir/flags.make
CMakeFiles/Isometric.dir/source/main.cpp.obj: CMakeFiles/Isometric.dir/includes_CXX.rsp
CMakeFiles/Isometric.dir/source/main.cpp.obj: ../source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\programming\cpp\Isometric\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Isometric.dir/source/main.cpp.obj"
	C:\programming\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Isometric.dir\source\main.cpp.obj -c C:\programming\cpp\Isometric\source\main.cpp

CMakeFiles/Isometric.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Isometric.dir/source/main.cpp.i"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\programming\cpp\Isometric\source\main.cpp > CMakeFiles\Isometric.dir\source\main.cpp.i

CMakeFiles/Isometric.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Isometric.dir/source/main.cpp.s"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\programming\cpp\Isometric\source\main.cpp -o CMakeFiles\Isometric.dir\source\main.cpp.s

CMakeFiles/Isometric.dir/source/Rendering.cpp.obj: CMakeFiles/Isometric.dir/flags.make
CMakeFiles/Isometric.dir/source/Rendering.cpp.obj: CMakeFiles/Isometric.dir/includes_CXX.rsp
CMakeFiles/Isometric.dir/source/Rendering.cpp.obj: ../source/Rendering.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\programming\cpp\Isometric\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Isometric.dir/source/Rendering.cpp.obj"
	C:\programming\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Isometric.dir\source\Rendering.cpp.obj -c C:\programming\cpp\Isometric\source\Rendering.cpp

CMakeFiles/Isometric.dir/source/Rendering.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Isometric.dir/source/Rendering.cpp.i"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\programming\cpp\Isometric\source\Rendering.cpp > CMakeFiles\Isometric.dir\source\Rendering.cpp.i

CMakeFiles/Isometric.dir/source/Rendering.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Isometric.dir/source/Rendering.cpp.s"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\programming\cpp\Isometric\source\Rendering.cpp -o CMakeFiles\Isometric.dir\source\Rendering.cpp.s

CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.obj: CMakeFiles/Isometric.dir/flags.make
CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.obj: CMakeFiles/Isometric.dir/includes_CXX.rsp
CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.obj: ../source/SimplexNoise.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\programming\cpp\Isometric\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.obj"
	C:\programming\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Isometric.dir\source\SimplexNoise.cpp.obj -c C:\programming\cpp\Isometric\source\SimplexNoise.cpp

CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.i"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\programming\cpp\Isometric\source\SimplexNoise.cpp > CMakeFiles\Isometric.dir\source\SimplexNoise.cpp.i

CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.s"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\programming\cpp\Isometric\source\SimplexNoise.cpp -o CMakeFiles\Isometric.dir\source\SimplexNoise.cpp.s

CMakeFiles/Isometric.dir/source/world_chunk.cpp.obj: CMakeFiles/Isometric.dir/flags.make
CMakeFiles/Isometric.dir/source/world_chunk.cpp.obj: CMakeFiles/Isometric.dir/includes_CXX.rsp
CMakeFiles/Isometric.dir/source/world_chunk.cpp.obj: ../source/world_chunk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\programming\cpp\Isometric\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Isometric.dir/source/world_chunk.cpp.obj"
	C:\programming\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Isometric.dir\source\world_chunk.cpp.obj -c C:\programming\cpp\Isometric\source\world_chunk.cpp

CMakeFiles/Isometric.dir/source/world_chunk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Isometric.dir/source/world_chunk.cpp.i"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\programming\cpp\Isometric\source\world_chunk.cpp > CMakeFiles\Isometric.dir\source\world_chunk.cpp.i

CMakeFiles/Isometric.dir/source/world_chunk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Isometric.dir/source/world_chunk.cpp.s"
	C:\programming\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\programming\cpp\Isometric\source\world_chunk.cpp -o CMakeFiles\Isometric.dir\source\world_chunk.cpp.s

# Object files for target Isometric
Isometric_OBJECTS = \
"CMakeFiles/Isometric.dir/source/main.cpp.obj" \
"CMakeFiles/Isometric.dir/source/Rendering.cpp.obj" \
"CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.obj" \
"CMakeFiles/Isometric.dir/source/world_chunk.cpp.obj"

# External object files for target Isometric
Isometric_EXTERNAL_OBJECTS =

Isometric.exe: CMakeFiles/Isometric.dir/source/main.cpp.obj
Isometric.exe: CMakeFiles/Isometric.dir/source/Rendering.cpp.obj
Isometric.exe: CMakeFiles/Isometric.dir/source/SimplexNoise.cpp.obj
Isometric.exe: CMakeFiles/Isometric.dir/source/world_chunk.cpp.obj
Isometric.exe: CMakeFiles/Isometric.dir/build.make
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libsfml-graphics-s.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libsfml-audio-s.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libsfml-window-s.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libfreetype.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libopenal32.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libsfml-system-s.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libvorbisfile.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libvorbisenc.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libvorbis.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libogg.a
Isometric.exe: C:/programming/cpp/Libraries/SFML-2.5.1/lib/libFLAC.a
Isometric.exe: CMakeFiles/Isometric.dir/linklibs.rsp
Isometric.exe: CMakeFiles/Isometric.dir/objects1.rsp
Isometric.exe: CMakeFiles/Isometric.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\programming\cpp\Isometric\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Isometric.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Isometric.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Isometric.dir/build: Isometric.exe

.PHONY : CMakeFiles/Isometric.dir/build

CMakeFiles/Isometric.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Isometric.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Isometric.dir/clean

CMakeFiles/Isometric.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\programming\cpp\Isometric C:\programming\cpp\Isometric C:\programming\cpp\Isometric\cmake-build-release C:\programming\cpp\Isometric\cmake-build-release C:\programming\cpp\Isometric\cmake-build-release\CMakeFiles\Isometric.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Isometric.dir/depend
