QT       += core gui network widgets webenginecore webenginewidgets webchannel quick sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basewindow.cpp \
    config.cpp \
    global.cpp \
    jsbridge.cpp \
    main.cpp \
    mainwindow.cpp \
    messagebox.cpp \
    requestmapper.cpp \
    titlebar.cpp \
    webpage.cpp \
    webview.cpp \
    widget.cpp \
    widgetcontext.cpp

HEADERS += \
    basewindow.h \
    config.h \
    global.h \
    jsbridge.h \
    mainwindow.h \
    messagebox.h \
    requestmapper.h \
    titlebar.h \
    webpage.h \
    webview.h \
    widget.h \
    widgetcontext.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Kapok_zh_CN.ts

DISTFILES += \
    etc/Config.ini \
    etc/Kapok.config.json

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(./QtWebApp/httpserver/httpserver.pri)
include(./QtWebApp/logging/logging.pri)
include(./QtWebApp/downloadmanager/downloadmanager.pri)
include(./QtWebApp/database/database.pri)
include(./QtWebApp/directory/directory.pri)

RESOURCES += \
    icon.qrc \
    resouces.qrc
