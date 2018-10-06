project(babel_server)
project(babel_client)
cmake_minimum_required(VERSION 3.5)
add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(Common)
include_directories(Server)
include_directories(.)

set(CMAKE_PREFIX_PATH /opt/Qt/5.11.2)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
include_directories(Client)

set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)

add_executable(babel_server
	Common/Chopper/Chopper.cpp
	Common/Network/BoostSocket.cpp
	Common/Network/ASocket.cpp
	Common/Protocol/Protocol.cpp
	Common/Opts/Opts.cpp
	Server/main.cpp
	Server/Client/Client.cpp
	Server/CoreServer/CoreServer.cpp
	Server/Resources/Resources.cpp
	Server/Db/Db.cpp
	Server/Db/DbData.cpp)

target_link_libraries(babel_server ${CONAN_LIBS})

add_executable(babel_client
	Common/Network/ASocket.cpp
	Common/Network/QtSocket.cpp
	Common/Opts/Opts.cpp
	Common/Protocol/Protocol.cpp
	Common/Chopper/Chopper.cpp
	Client/PaWrapper/PaWrapper.cpp
	Client/clientprotocol.cpp
	Client/main.cpp
	Client/clientmainwindows.cpp
	Client/singletons.cpp
	Client/cache.cpp
	Client/version.cpp
	Client/about.cpp
	Client/frienditem.cpp
	Client/conv.cpp
	Client/login.cpp
	Client/mainscreen.cpp
	Client/listfrienditem.cpp
	Client/settings.cpp
	Client/friendsmanager.cpp
	Client/callform.cpp
	Client/call.cpp
	Client/soundwrapper.cpp
	Client/udpwrapper.cpp
	Client/resources.qrc
)

target_link_libraries(babel_client
	Qt5::Widgets
	Qt5::Network
	Qt5::Core
	${CONAN_LIBS})

SET_TARGET_PROPERTIES(babel_client PROPERTIES
  COMPILE_FLAGS "-std=gnu++1z -Wno-missing-field-initializers -DVERSION=0.0.1"
)