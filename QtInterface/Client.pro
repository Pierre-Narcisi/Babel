#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T18:12:07
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:DEFINES   += TARGET_WINDOWS
unix:DEFINES    += TARGET_UNIX
macos:DEFINES   += TARGET_MACOS

CLIENT_VERSION = 0.1.0

TARGET = Babel-Client
TEMPLATE = app

RC_FILE = Client.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS "VERSION=$$CLIENT_VERSION"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:LIBS  += $$PWD/libs/Json/windows/Json.dll
unix:LIBS   += -L$$PWD/libs/Json/linux -lstatic_Json
macos:LIBS  += -L$$PWD/libs/Json/macsos -lstatic_Json

INCLUDEPATH =   $$PWD/libs/Json/includes

SOURCES += \
    main.cpp \
    clientmainwindows.cpp \
    listgameitem.cpp \
    singletons.cpp \
    cache.cpp \
    version.cpp \
    about.cpp \
    frienditem.cpp \
    conv.cpp \
    login.cpp

HEADERS += \
    clientmainwindows.h \
    listgameitem.h \
    singletons.h \
    cache.h \
    version.h \
    about.h \
    frienditem.h \
    conv.h \
    login.h

FORMS += \
    clientmainwindows.ui \
    about.ui \
    frienditem.ui \
    conv.ui \
    login.ui

RESOURCES += \
    resources.qrc
