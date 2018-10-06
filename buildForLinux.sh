#!/bin/bash
##
## EPITECH PROJECT, 2018
## babel
## File description:
## buildForLinux.sh
##

conan remote add bincrafter https://api.bintray.com/conan/bincrafters/public-conan

rootPath="$(
	cd "$(dirname "$0")"
	pwd -P
)/.";

if [ "$DEBUG" != "1" ]; then
	BUILD_TYPE="Release"
else
	BUILD_TYPE="Debug"
fi

export CC=gcc
export CXX=g++
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
conan install .. --build=missing --profile ../conanPlatformSettings/linux.txt
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. -G "Unix Makefiles";
cmake -build .
make $@ $ARGS

rootPath="$(
	cd "$(dirname "$0")"
	pwd -P
)/.";

