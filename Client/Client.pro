#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T18:12:07
#
#-------------------------------------------------

QT       += core gui network

QMAKE_CXXFLAGS += -std=c++17 -Wno-missing-field-initializers
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:DEFINES   += TARGET_WINDOWS
unix:DEFINES    += TARGET_UNIX
macos:DEFINES   += TARGET_MACOS

CLIENT_VERSION = 0.0.1

TARGET = babel_client
TEMPLATE = app

RC_FILE = Client.rc

COMMON_PATH = $$PWD/../Common
SOUND_UTILS = $$PWD/SoundUtils

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS "VERSION=$$CLIENT_VERSION"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#win32:LIBS  += $$PWD/libs/Json/windows/Json.dll
#unix:LIBS   += -L$$SOUND_UTILS/lib -lportaudio
#macos:LIBS  += -L$$PWD/libs/Json/macsos -lstatic_Json

INCLUDEPATH = $$COMMON_PATH

SOURCES += \
    $$COMMON_PATH/Network/ASocket.cpp \
    $$COMMON_PATH/Network/QtSocket.cpp \
    $$COMMON_PATH/Opts/Opts.cpp \
    $$COMMON_PATH/Protocol/Protocol.cpp \
    $$COMMON_PATH/Chopper/Chopper.cpp \
#    $$SOUND_UTILS/PaWrapper.cpp \
    clientprotocol.cpp \
    main.cpp \
    clientmainwindows.cpp \
    singletons.cpp \
    cache.cpp \
    version.cpp \
    about.cpp \
    frienditem.cpp \
    conv.cpp \
    login.cpp \
    mainscreen.cpp \
    listfrienditem.cpp \
    settings.cpp \
    call.cpp \
    friendsmanager.cpp \
    callform.cpp \
    soundwrapper.cpp \
    ../src/PaWrapper.cpp \
    udpwrapper.cpp \
    usersettings.cpp

HEADERS += \
    $$COMMON_PATH/Protocol/Protocol.h \
    $$COMMON_PATH/Network/ISocket.hpp \
    $$COMMON_PATH/Network/ASocket.hpp \
    $$COMMON_PATH/Network/QtSocket.hpp \
    $$COMMON_PATH/Opts/Opts.hpp \
    $$COMMON_PATH/Constant.hpp \
    $$COMMON_PATH/Chopper/Chopper.hpp \
#    $$SOUND_UTILS/PaWrapper.hpp \
    clientprotocol.h \
    clientmainwindows.h \
    singletons.h \
    cache.h \
    version.h \
    about.h \
    frienditem.h \
    conv.h \
    login.h \
    mainscreen.h \
    listfrienditem.h \
    settings.h \
    call.h \
    friendsmanager.h \
    callform.h \
    soundwrapper.h \
    ../src/PaWrapper.hpp \
    udpwrapper.h \
    usersettings.h

FORMS += \
    clientmainwindows.ui \
    about.ui \
    frienditem.ui \
    conv.ui \
    login.ui \
    mainscreen.ui \
    callform.ui \
    usersettings.ui

RESOURCES += \
    resources.qrc
