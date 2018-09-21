QT += gui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    encoder.cpp \
    decoder.cpp \
    dictionary.cpp

HEADERS += \
    encoder.h \
    decoder.h \
    dictionary.h
