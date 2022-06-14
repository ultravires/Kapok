INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core network

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/downloadmanager.h \
    $$PWD/textprogressbar.h

SOURCES += \
    $$PWD/downloadmanager.cpp \
    $$PWD/textprogressbar.cpp
