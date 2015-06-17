QT       += quick qml xml widgets
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    StarEnglishGenerator.h \
    StarEnglishGeneratorModel.h \
    LanguageSelector.h

SOURCES += \
    StarEnglishGenerator.cpp \
    StarEnglishGeneratorModel.cpp \
    LanguageSelector.cpp

QMAKE_CXXFLAGS += -std=c++0x
