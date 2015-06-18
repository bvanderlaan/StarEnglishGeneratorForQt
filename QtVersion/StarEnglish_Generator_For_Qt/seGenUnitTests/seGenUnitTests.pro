TEMPLATE = app
QT       += core testlib xml
QT       -= gui

CONFIG   += console
CONFIG   += testcase
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    StarEnglishGeneratorTestSuite.cpp \
    StarEnglishGeneratorModelTestSuite.cpp \
    StarEnglishGeneratorFake.cpp \
    LongEnglishGeneratorTestSuite.cpp \
    StarEnglishGenerationCommandTestSuite.cpp \
    StarEnglishGenerationCommandSkipIOCheck.cpp \
    LongEnglishGenerationCommandSkipIOCheck.cpp \
    LongEnglishGenerationCommandTestSuite.cpp \
    LongEnglishGeneratorFake.cpp

HEADERS += \
    StarEnglishGeneratorTestSuite.h \
    StarEnglishGeneratorModelTestSuite.h \
    StarEnglishGeneratorFake.h \
    LongEnglishGeneratorTestSuite.hpp \
    StarEnglishGenerationCommandTestSuite.hpp \
    StarEnglishGenerationCommandSkipIOCheck.hpp \
    LongEnglishGenerationCommandSkipIOCheck.hpp \
    LongEnglishGenerationCommandTestSuite.hpp \
    LongEnglishGeneratorFake.hpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../starenglishgeneratorlib/release/ -lstarenglishgeneratorlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../starenglishgeneratorlib/debug/ -lstarenglishgeneratorlib
else:unix: LIBS += -L$$OUT_PWD/../starenglishgeneratorlib/ -lstarenglishgeneratorlib

INCLUDEPATH += $$PWD/../starenglishgeneratorlib
DEPENDPATH += $$PWD/../starenglishgeneratorlib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../starenglishgeneratorlib/release/libstarenglishgeneratorlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../starenglishgeneratorlib/debug/libstarenglishgeneratorlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../starenglishgeneratorlib/release/starenglishgeneratorlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../starenglishgeneratorlib/debug/starenglishgeneratorlib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../starenglishgeneratorlib/libstarenglishgeneratorlib.a
