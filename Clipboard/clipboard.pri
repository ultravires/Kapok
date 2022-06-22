INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += gui

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/clipboard.h

SOURCES += \
    $$PWD/clipboard.cpp
