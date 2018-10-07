#!/bin/bash
##
## EPITECH PROJECT, 2018
## babel
## File description:
## buildForLinux.sh
##

## RUN ME WITH GIT BASH FOR WINDOWS

rootPath="$(
	cd "$(dirname "$0")"
	pwd -P
)/.";

mkdir buildWindows
cd buildWindows

conan install .. --build missing --profile ../conanPlatformSettings/windows.txt
cmake -G "Visual Studio 15 Win64" ..
cmake -build .