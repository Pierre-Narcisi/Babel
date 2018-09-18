cmake_minimum_required(VERSION 3.10)
project(babel C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(project)

add_executable(babel
	project/Client.h
	project/Server.h)
