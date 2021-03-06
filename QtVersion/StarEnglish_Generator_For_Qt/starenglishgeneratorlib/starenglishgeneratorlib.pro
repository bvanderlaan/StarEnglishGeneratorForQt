QT       += quick qml xml widgets
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    StarEnglishGenerator.h \
    StarEnglishGeneratorModel.h \
    LanguageSelector.h \
    TranslationGenerator.hpp \
    LongEnglishGenerator.hpp \
    StarEnglishGenerationCommand.hpp \
    BaseGenerationCommand.hpp \
    LongEnglishGenerationCommand.hpp

SOURCES += \
    StarEnglishGenerator.cpp \
    StarEnglishGeneratorModel.cpp \
    LanguageSelector.cpp \
    TranslationGenerator.cpp \
    LongEnglishGenerator.cpp \
    StarEnglishGenerationCommand.cpp \
    BaseGenerationCommand.cpp \
    LongEnglishGenerationCommand.cpp

QMAKE_CXXFLAGS += -std=c++0x
