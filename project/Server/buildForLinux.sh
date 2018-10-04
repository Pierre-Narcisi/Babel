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

export CC=gcc
export CXX=g++
COMPILER_MAJOR=$(touch test.c && $CC -E -dM test.c  | grep -o '__GNUC__ [[:digit:]]' | cut -d' ' -f2)
COMPILER_MINOR=$(touch test.c && $CC -E -dM test.c  | grep -o '__GNUC_MINOR__ [[:digit:]]' | cut -d' ' -f2)
rm test.c

cd $rootPath;

mkdir build;
cd build;
conan install .. --build missing -s "compiler=gcc" -s "compiler.version=$COMPILER_MAJOR.$COMPILER_MINOR" -s "compiler.libcxx=libstdc++11";
cmake -DCMAKE_BUILD_TYPE=Debug .. -G "Unix Makefiles";
cmake -build .
make $@
