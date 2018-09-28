Project(babel-client)
cmake_minimum_required(VERSION 3.5)
add_definitions("-std=c++17")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(libs/cobject/includes)
include_directories(../Common)
include_directories(..)
include_directories(.)

add_executable(babel-client
	../Common/Chopper/Chopper.cpp
	../Common/Network/BoostSocket.cpp
	../Common/Opts/Opts.cpp
	main.cpp
	Client/Client.cpp
	CoreServer/CoreServer.cpp
	../Db/Db.cpp
	../Db/DbData.cpp)
 target_link_libraries(babel-client ${CONAN_LIBS})