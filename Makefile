# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /home/seb/CLion-2018.2.4/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/seb/CLion-2018.2.4/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seb/babel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seb/babel

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/seb/CLion-2018.2.4/clion-2018.2.4/bin/cmake/linux/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/seb/CLion-2018.2.4/clion-2018.2.4/bin/cmake/linux/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/seb/babel/CMakeFiles /home/seb/babel/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/seb/babel/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named babel

# Build rule for target.
babel: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 babel
.PHONY : babel

# fast build rule for target.
babel/fast:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/build
.PHONY : babel/fast

test/Main.o: test/Main.cpp.o

.PHONY : test/Main.o

# target to build an object file
test/Main.cpp.o:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/Main.cpp.o
.PHONY : test/Main.cpp.o

test/Main.i: test/Main.cpp.i

.PHONY : test/Main.i

# target to preprocess a source file
test/Main.cpp.i:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/Main.cpp.i
.PHONY : test/Main.cpp.i

test/Main.s: test/Main.cpp.s

.PHONY : test/Main.s

# target to generate assembly for a file
test/Main.cpp.s:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/Main.cpp.s
.PHONY : test/Main.cpp.s

test/PaWrapper.o: test/PaWrapper.cpp.o

.PHONY : test/PaWrapper.o

# target to build an object file
test/PaWrapper.cpp.o:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/PaWrapper.cpp.o
.PHONY : test/PaWrapper.cpp.o

test/PaWrapper.i: test/PaWrapper.cpp.i

.PHONY : test/PaWrapper.i

# target to preprocess a source file
test/PaWrapper.cpp.i:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/PaWrapper.cpp.i
.PHONY : test/PaWrapper.cpp.i

test/PaWrapper.s: test/PaWrapper.cpp.s

.PHONY : test/PaWrapper.s

# target to generate assembly for a file
test/PaWrapper.cpp.s:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/PaWrapper.cpp.s
.PHONY : test/PaWrapper.cpp.s

test/Test.o: test/Test.cpp.o

.PHONY : test/Test.o

# target to build an object file
test/Test.cpp.o:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/Test.cpp.o
.PHONY : test/Test.cpp.o

test/Test.i: test/Test.cpp.i

.PHONY : test/Test.i

# target to preprocess a source file
test/Test.cpp.i:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/Test.cpp.i
.PHONY : test/Test.cpp.i

test/Test.s: test/Test.cpp.s

.PHONY : test/Test.s

# target to generate assembly for a file
test/Test.cpp.s:
	$(MAKE) -f CMakeFiles/babel.dir/build.make CMakeFiles/babel.dir/test/Test.cpp.s
.PHONY : test/Test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... babel"
	@echo "... test/Main.o"
	@echo "... test/Main.i"
	@echo "... test/Main.s"
	@echo "... test/PaWrapper.o"
	@echo "... test/PaWrapper.i"
	@echo "... test/PaWrapper.s"
	@echo "... test/Test.o"
	@echo "... test/Test.i"
	@echo "... test/Test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

