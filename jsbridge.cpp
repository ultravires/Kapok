#include "jsbridge.h"
#include "QtCore/qurl.h"
#include "widget.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScreen>
#include <QUrl>

JSBridge::JSBridge( QWidget *widget )
    : QObject() {
    this->widget = widget;
}

void JSBridge::message( QString title, QString text ) {
    QMessageBox::information( widget, title, text,
                              QMessageBox::StandardButton::Ok );
}

bool JSBridge::question( QString title, QString question ) {
    if ( QMessageBox::question( widget, title, question ) ==
         QMessageBox::Yes ) {
        return true;
    }
    return false;
}

bool JSBridge::confirm( QString title, QString question ) {
    if ( QMessageBox::question( widget, title, question,
                                QMessageBox::Cancel | QMessageBox::Ok ) ==
         QMessageBox::Yes ) {
        return true;
    }
    return false;
}

void JSBridge::warning( QString title, QString message ) {
    QMessageBox::warning( widget, title, message );
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
    int clientWidth     = widget->width();
    int clientHeight    = widget->height();
    int availableWidth  = widget->screen()->availableSize().width();
    int availableHeight = widget->screen()->availableSize().height();
    int left            = ( availableWidth - clientWidth ) / 2;
    int top             = ( availableHeight - clientHeight ) / 2;
    widget->move( left, top );
}

void JSBridge::move( int left, int top ) { widget->move( left, top ); }

void JSBridge::close() { widget->close(); }

void JSBridge::quit() {
    qApp->setQuitOnLastWindowClosed( true );
    qApp->closeAllWindows();
    qApp->exit();
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

void JSBridge::setResizable( bool resizable ) {}

void JSBridge::resize( int width, int height ) {
    widget->resize( width, height );
}

void JSBridge::open( QString uniqueLabel, QString options ) {
    QJsonDocument jsonDocument =
        QJsonDocument::fromJson( options.toLocal8Bit().data() );
    if ( !jsonDocument.isNull() ) {
        QJsonObject jsonObject  = jsonDocument.object();
        QJsonValue  url         = jsonObject.value( "url" );
        QJsonValue  width       = jsonObject.value( "width" );
        QJsonValue  height      = jsonObject.value( "height" );
        QJsonValue  top         = jsonObject.value( "top" );
        QJsonValue  left        = jsonObject.value( "left" );
        QJsonValue  visible     = jsonObject.value( "visible" );
        QJsonValue  decorations = jsonObject.value( "decorations" );
        setDecorations( decorations.toBool() );
        Widget *widget = new Widget();
        widget->resize( width.toInt(), height.toInt() );
        widget->move( left.toInt(), top.toInt() );
        widget->webview->load( QUrl( url.toString() ) );
        if ( visible.toBool() ) {
            widget->show();
        }
    }
}
