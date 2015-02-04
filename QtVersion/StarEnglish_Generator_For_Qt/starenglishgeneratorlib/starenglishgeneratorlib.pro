QT       += quick qml xml
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    StarEnglishGenerator.h \
    StarEnglishGeneratorModel.h

SOURCES += \
    StarEnglishGenerator.cpp \
    StarEnglishGeneratorModel.cpp

QMAKE_CXXFLAGS += -std=c++0x
