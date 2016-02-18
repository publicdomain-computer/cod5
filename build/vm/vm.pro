TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../include
QMAKE_CXXFLAGS += -std=c++14

SOURCES += ../../appsrc/vm/main.cpp

