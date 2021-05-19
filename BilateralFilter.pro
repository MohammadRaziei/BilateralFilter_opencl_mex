TEMPLATE = app
CONFIG += console c++17
#CONFIG -= app_bundle
#CONFIG -= qt

include(opencl.pri)
#include(opencv.pri)

SOURCES += \
        main.cpp

DISTFILES += \
    kernel.cl

HEADERS += \
    global.h \
    opencl.h



