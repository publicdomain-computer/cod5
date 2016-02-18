TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../include
QMAKE_CXXFLAGS += -std=c++14

SOURCES += \
    ../../appsrc/cxx/main.cpp


# HEADERS +=


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../c5/release/ -lc5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../c5/debug/ -lc5
else:unix: LIBS += -L$$OUT_PWD/../c5/ -lc5

INCLUDEPATH += $$PWD/../c5
DEPENDPATH += $$PWD/../c5
