TEMPLATE = app

QT += qml xml quick widgets

SOURCES += main.cpp

RESOURCES += qml.qrc

QMAKE_CXXFLAGS += -std=c++0x

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

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


# The below allows lupdate/lrelease to see the QML files
lupdate_only{
    SOURCES += 	*.qml
}
