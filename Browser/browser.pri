INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += webenginewidgets

HEADERS += \
    $$PWD/browser.h \
    $$PWD/browserwindow.h \
    $$PWD/downloadmanagerwidget.h \
    $$PWD/downloadwidget.h \
    $$PWD/tabwidget.h \
    $$PWD/webpage.h \
    $$PWD/webpopupwindow.h \
    $$PWD/webview.h

SOURCES += \
    $$PWD/browser.cpp \
    $$PWD/browserwindow.cpp \
    $$PWD/downloadmanagerwidget.cpp \
    $$PWD/downloadwidget.cpp \
    $$PWD/main.cpp \
    $$PWD/tabwidget.cpp \
    $$PWD/webpage.cpp \
    $$PWD/webpopupwindow.cpp \
    $$PWD/webview.cpp

FORMS += \
    $$PWD/certificateerrordialog.ui \
    $$PWD/passworddialog.ui \
    $$PWD/downloadmanagerwidget.ui \
    $$PWD/downloadwidget.ui

RESOURCES += $$PWD/data/simplebrowser.qrc
