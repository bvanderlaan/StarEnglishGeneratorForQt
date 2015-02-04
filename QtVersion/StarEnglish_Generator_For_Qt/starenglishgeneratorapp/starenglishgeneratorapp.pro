TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

RESOURCES += qml.qrc

QMAKE_CXXFLAGS += -std=c++0x

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += $$PWD/../starenglishgeneratorlib

CONFIG(release, debug|release): LIBS += -L../starenglishgeneratorlib/release/ -lstarenglishgeneratorlib
else:CONFIG(debug, debug|release): LIBS += -L../starenglishgeneratorlib/debug/ -lstarenglishgeneratorlib

HEADERS +=
