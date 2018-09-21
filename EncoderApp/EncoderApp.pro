TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    encoder.cpp \
    decoder.cpp \
    dictionary.cpp

HEADERS += \
    encoder.h \
    decoder.h \
    dictionary.h
