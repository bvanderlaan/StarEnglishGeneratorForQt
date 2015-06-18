QT       += quick qml xml widgets
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    StarEnglishGenerator.h \
    StarEnglishGeneratorModel.h \
    LanguageSelector.h \
    TranslationGenerator.hpp \
    LongEnglishGenerator.hpp

SOURCES += \
    StarEnglishGenerator.cpp \
    StarEnglishGeneratorModel.cpp \
    LanguageSelector.cpp \
    TranslationGenerator.cpp \
    LongEnglishGenerator.cpp

QMAKE_CXXFLAGS += -std=c++0x
