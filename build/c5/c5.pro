#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T15:42:46
#
#-------------------------------------------------

QT       -= core gui

TARGET = c5
TEMPLATE = lib
CONFIG += staticlib

DEFINES += C5_LIBRARY

INCLUDEPATH += $$PWD/../../include
QMAKE_CXXFLAGS += -std=c++14

SOURCES += \
    ../../src/cxx/compiler.cpp \
    ../../src/cxx/env.cpp \
    ../../src/cxx/preprocessor.cpp \
    ../../src/cxx/pretokens.cpp


HEADERS += \
    ../../include/c5/cxx/compiler.h \
    ../../include/c5/cxx/env.h \
    ../../include/c5/cxx/preprocessor.h \
    ../../include/c5/cxx/pretokens.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
