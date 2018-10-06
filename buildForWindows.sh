#!/bin/bash
##
## EPITECH PROJECT, 2018
## babel
## File description:
## buildForLinux.sh
##

rootPath="$(
	cd "$(dirname "$0")"
	pwd -P
)/.";

toolchain=/usr/bin/x86_64-w64-mingw32
target_host=x86_64-w64-mingw32
cc_compiler=gcc
cxx_compiler=g++

COMPILER_MAJOR=$(touch test.c && $CC -E -dM test.c  | grep -o '__GNUC__ [[:digit:]]' | cut -d' ' -f2)
COMPILER_MINOR=$(touch test.c && $CC -E -dM test.c  | grep -o '__GNUC_MINOR__ [[:digit:]]' | cut -d' ' -f2)
rm test.c

if [ "$COMPILER_MINOR" == "0" ]; then
	COMPILER_VERSION=$COMPILER_MAJOR
else
	COMPILER_VERSION=$COMPILER_MAJOR.$COMPILER_MINOR;
fi

cd $rootPath;

mkdir build;
cd build;
conan install .. --build=missing --profile ../conanPlatformSettings/linux_to_windows.txt
cmake -DCMAKE_BUILD_TYPE=Debug .. -G "Unix Makefiles";
cmake -build .
make $@