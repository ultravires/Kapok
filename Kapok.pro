QT       += core gui network webenginecore webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global.cpp \
    jsbridge.cpp \
    main.cpp \
    mainwindow.cpp \
    requestmapper.cpp \
    webpage.cpp \
    webview.cpp \
    widget.cpp

HEADERS += \
    global.h \
    jsbridge.h \
    mainwindow.h \
    requestmapper.h \
    webpage.h \
    webview.h \
    widget.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Kapok_zh_CN.ts

DISTFILES += \
    etc/Config.ini

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(./QtWebApp/httpserver/httpserver.pri)
include(./QtWebApp/logging/logging.pri)
#include(./Browser/browser.pri)
