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

cd $rootPath;

mkdir build;
cd build;
conan install .. --build missing -s "compiler=gcc" -s "compiler.libcxx=libstdc++11";
cmake -DCMAKE_BUILD_TYPE=Debug .. -G "Unix Makefiles";
cmake -build .
make $@