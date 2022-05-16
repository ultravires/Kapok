#include "jsbridge.h"
#include "QtCore/qurl.h"
#include "widget.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

JSBridge::JSBridge( QWidget *widget )
    : QObject() {
    this->widget = widget;
}

void JSBridge::showInfoMessageBox( QString title, QString text ) {
    QMessageBox::information( widget, title, text,
                              QMessageBox::StandardButton::Ok );
}

void JSBridge::setFullScreen( bool isFullScreen ) {
    if ( isFullScreen ) {
        widget->showFullScreen();
    } else {
        widget->showNormal();
    }
}

void JSBridge::maximize() { widget->showMaximized(); }

void JSBridge::minimize() { widget->showMinimized(); }

void JSBridge::normal() { widget->showNormal(); }

void JSBridge::toggleMaximize() {
    if ( widget->isMaximized() ) {
        widget->showNormal();
    } else {
        widget->showMaximized();
    }
}

bool JSBridge::isMaximize() { return widget->isMaximized(); }

void JSBridge::center() {
    // empty
}

void JSBridge::close() { widget->close(); }

void JSBridge::quit() {
    qApp->setQuitOnLastWindowClosed( true );
    qApp->closeAllWindows();
    qApp->exit();
}

void JSBridge::open( QString uniqueLabel, QString options ) {
    QJsonDocument jsonDocument =
        QJsonDocument::fromJson( options.toLocal8Bit().data() );
    if ( !jsonDocument.isNull() ) {
        QJsonObject jsonObject = jsonDocument.object();
        QJsonValue  url        = jsonObject.value( "url" );
        Widget     *widget     = new Widget();
        widget->resize( 500, 500 );
        widget->load( QUrl( url.toString() ) );
        widget->show();
    }
}

void JSBridge::setDecorations( bool decorations ) {
    if ( decorations ) {
        widget->setWindowFlag( Qt::Window, true );
        widget->setWindowFlag( Qt::FramelessWindowHint, false );
        widget->show();
    } else {
        widget->setWindowFlag( Qt::Window, true );
        widget->setWindowFlag( Qt::FramelessWindowHint, true );
        widget->show();
    }
}

bool JSBridge::isDecorations() {
    return widget->windowFlags().testFlag( Qt::FramelessWindowHint );
}

void JSBridge::setTitle( QString title ) { widget->setWindowTitle( title ); }
