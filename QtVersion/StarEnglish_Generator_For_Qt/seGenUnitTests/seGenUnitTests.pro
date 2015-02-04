TEMPLATE = app
QT       += core testlib
QT       -= gui

CONFIG   += console
CONFIG   += testcase
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    StarEnglishGeneratorTestSuite.cpp \
    StarEnglishGeneratorModelTestSuite.cpp \
    StarEnglishGeneratorFake.cpp \
    StarEnglishGeneratorModelTester.cpp

HEADERS += \
    StarEnglishGeneratorTestSuite.h \
    StarEnglishGeneratorModelTestSuite.h \
    StarEnglishGeneratorFake.h \
    StarEnglishGeneratorModelTester.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
INCLUDEPATH += $$PWD/../starenglishgeneratorlib

CONFIG(release, debug|release): LIBS += -L../starenglishgeneratorlib/release/ -lstarenglishgeneratorlib
else:CONFIG(debug, debug|release): LIBS += -L../starenglishgeneratorlib/debug/ -lstarenglishgeneratorlib
