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
conan install .. -s compiler=gcc;
cmake -DCMAKE_BUILD_TYPE=Debug .. -G "Unix Makefiles";
cmake -build .
make $@