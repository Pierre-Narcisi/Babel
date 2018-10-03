Project(babel_server)
cmake_minimum_required(VERSION 3.5)
add_definitions("-std=c++17")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(libs/cobject/includes)
include_directories(../Common)
include_directories(..)
include_directories(.)

add_executable(babel_server
	../Common/Chopper/Chopper.cpp
	../Common/Network/BoostSocket.cpp
	../Common/Protocol/Protocol.cpp
	../Common/Opts/Opts.cpp
	main.cpp
	Client/Client.cpp
	Client/ServerProtocol.cpp
	CoreServer/CoreServer.cpp
	Resources/Resources.cpp
	UdpRelayServer/UdpRelayServer.cpp
	../Db/Db.cpp
	../Db/DbData.cpp)
 target_link_libraries(babel_server ${CONAN_LIBS})