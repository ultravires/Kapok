#include "jsbridge.h"
#include "messagebox.h"
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

void JSBridge::message( const QString &title, const QString &text ) {
    MessageBox::message( widget, title, text );
}

bool JSBridge::ask( QString title, QString text ) {
    return MessageBox::ask( widget, title, text );
}

bool JSBridge::confirm( QString title, QString text ) {
    return MessageBox::confirm( widget, title, text );
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
    int clientWidth  = widget->width();
    int clientHeight = widget->height();
    int availableWidth =
        QApplication::primaryScreen()->availableGeometry().width();
    int availableHeight =
        QApplication::primaryScreen()->availableGeometry().height();
    int left = ( availableWidth - clientWidth ) / 2;
    int top  = ( availableHeight - clientHeight ) / 2;
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

void JSBridge::resize( int width, int height ) {
    widget->resize( width, height );
}

void JSBridge::show() { widget->show(); }

void JSBridge::setGeometry( int left, int top, int width, int height ) {
    widget->setGeometry( left, top, width, height );
}

///** Configuration for the window to create. */
// interface WindowOptions {
//     /**
//      * Remote URL or local file path to open.
//      *
//      * - URL such as `https://github.com/tauri-apps` is opened directly on a
//      * Tauri window.
//      * - data: URL such as `data:text/html,<html>...` is only supported with
//      the
//      * `window-data-url` Cargo feature for the `tauri` dependency.
//      * - local file path or route such as `/path/to/page.html` or `/users` is
//      * appended to the application URL (the devServer URL on development, or
//      * `tauri://localhost/` and `https://tauri.localhost/` on production).
//      */
//     url ?: string;
//     /** Show window in the center of the screen.. */
//     center ?: boolean;
//     /** The initial vertical position. Only applies if `y` is also set. */
//     x ?: number;
//     /** The initial horizontal position. Only applies if `x` is also set. */
//     y ?: number;
//     /** The initial width. */
//     width ?: number;
//     /** The initial height. */
//     height ?: number;
//     /** The minimum width. Only applies if `minHeight` is also set. */
//     minWidth ?: number;
//     /** The minimum height. Only applies if `minWidth` is also set. */
//     minHeight ?: number;
//     /** The maximum width. Only applies if `maxHeight` is also set. */
//     maxWidth ?: number;
//     /** The maximum height. Only applies if `maxWidth` is also set. */
//     maxHeight ?: number;
//     /** Whether the window is resizable or not. */
//     resizable ?: boolean;
//     /** Window title. */
//     title ?: string;
//     /** Whether the window is in fullscreen mode or not. */
//     fullscreen ?: boolean;
//     /** Whether the window will be initially hidden or focused. */
//     focus ?: boolean;
//     /**
//      * Whether the window is transparent or not.
//      * Note that on `macOS` this requires the `macos-private-api` feature
//      flag,
//      * enabled under `tauri.conf.json > tauri > macosPrivateApi`. WARNING:
//      Using
//      * private APIs on `macOS` prevents your application from being accepted
//      for
//      * the `App Store`.
//      */
//     transparent ?: boolean;
//     /** Whether the window should be maximized upon creation or not. */
//     maximized ?: boolean;
//     /** Whether the window should be immediately visible upon creation or
//     not.
//      */
//     visible ?: boolean;
//     /** Whether the window should have borders and bars or not. */
//     decorations ?: boolean;
//     /** Whether the window should always be on top of other windows or not.
//     */ alwaysOnTop ?: boolean;
//     /** Whether or not the window icon should be added to the taskbar. */
//     skipTaskbar ?: boolean;
//     /**
//      * Whether the file drop is enabled or not on the webview. By default it
//      is
//      * enabled.
//      *
//      * Disabling it is required to use drag and drop on the frontend on
//      Windows.
//      */
//     fileDropEnabled ?: boolean;
// }

void JSBridge::open( QString uniqueLabel, QString options ) {
    if ( uniqueLabel.isEmpty() ) {
        return;
    }
    QJsonDocument jsonDocument =
        QJsonDocument::fromJson( options.toLocal8Bit().data() );
    if ( !jsonDocument.isNull() ) {
        QJsonObject jsonObject = jsonDocument.object();
        // 窗口地址
        QString url = "";
        // 窗口是否居中
        bool center = true;
        // 距离屏幕左边的位置
        int x = 0;
        // 距离屏幕上边的位置
        int y = 0;
        // 窗口的宽度
        int width = this->widget->width();
        // 窗口的高度
        int height = this->widget->height();
        // 窗口的最小宽度
        int minWidth = this->widget->minimumWidth();
        // 窗口的最小高度
        int minHeight = this->widget->minimumHeight();
        // 窗口的最大宽度
        int maxWidth = this->widget->maximumWidth();
        // 窗口的最大高度
        int maxHeight = this->widget->maximumHeight();
        // 是否可改变窗口大小
        bool resizable = false;
        // 窗口标题
        QString title = this->widget->windowTitle();
        // 窗口是否全屏化
        bool fullscreen = this->widget->isFullScreen();
        // 窗口最初是隐藏还是聚焦
        bool focus = true;
        // 窗口是否透明
        bool transparent =
            this->widget->testAttribute( Qt::WA_TranslucentBackground );
        // 窗口是否最大化
        bool maximized = this->widget->isMaximized();
        // 窗口是否应在创建时立即可见
        bool visible = true;
        // 窗口是否具有默认边框和栏
        bool decorations =
            this->widget->windowFlags().testFlag( Qt::FramelessWindowHint );
        // 窗口是否置顶
        bool skipTaskbar = false;
        // 窗口图标是否在任务栏展示
        bool alwaysOnTop =
            this->widget->windowFlags().testFlag( Qt::WindowStaysOnTopHint );
        // 是否启用文件拖放
        bool fileDropEnabled = true;

        if ( jsonObject.contains( "url" ) ) {
            url = jsonObject.value( "url" ).toString();
        }
        if ( jsonObject.contains( "center" ) ) {
            center = jsonObject.value( "center" ).toBool();
        }
        if ( jsonObject.contains( "x" ) && jsonObject.contains( "y" ) ) {
            x = jsonObject.value( "left" ).toInt();
            y = jsonObject.value( "top" ).toInt();
        }
        if ( jsonObject.contains( "left" ) && jsonObject.contains( "top" ) ) {
            x = jsonObject.value( "left" ).toInt();
            y = jsonObject.value( "top" ).toInt();
        }
        if ( jsonObject.contains( "width" ) ) {
            width = jsonObject.value( "width" ).toInt();
        }
        if ( jsonObject.contains( "height" ) ) {
            height = jsonObject.value( "height" ).toInt();
        }
        if ( jsonObject.contains( "visible" ) ) {
            visible = jsonObject.value( "visible" ).toBool();
        }
        if ( jsonObject.contains( "decorations" ) ) {
            decorations = jsonObject.value( "decorations" ).toBool();
        }
        if ( jsonObject.contains( "minWidth" ) ) {
            minWidth = jsonObject.value( "minWidth" ).toInt();
        }
        if ( jsonObject.contains( "minHeight" ) ) {
            minHeight = jsonObject.value( "minHeight" ).toInt();
        }
        if ( jsonObject.contains( "maxWidth" ) ) {
            maxWidth = jsonObject.value( "maxWidth" ).toInt();
        }
        if ( jsonObject.contains( "maxHeight" ) ) {
            maxHeight = jsonObject.value( "maxHeight" ).toInt();
        }
        if ( jsonObject.contains( "fullscreen" ) ) {
            fullscreen = jsonObject.value( "fullscreen" ).toBool();
        }
        if ( jsonObject.contains( "focus" ) ) {
            focus = jsonObject.value( "focus" ).toBool();
        }
        if ( jsonObject.contains( "alwaysOnTop" ) ) {
            alwaysOnTop = jsonObject.value( "alwaysOnTop" ).toBool();
        }
        Widget *widget = new Widget();
        if ( decorations ) {
            widget->setWindowFlag( Qt::Window, true );
            widget->setWindowFlag( Qt::FramelessWindowHint, true );
        } else {
            widget->setWindowFlag( Qt::Window, true );
            widget->setWindowFlag( Qt::FramelessWindowHint, false );
        }
        if ( alwaysOnTop ) {
            widget->setWindowFlag( Qt::WindowStaysOnTopHint, true );
        } else {
            widget->setWindowFlag( Qt::WindowStaysOnTopHint, false );
        }
        if ( transparent ) {
            widget->setAttribute( Qt::WA_TranslucentBackground, true );
        } else {
            widget->setAttribute( Qt::WA_TranslucentBackground, false );
        }
        widget->setMinimumWidth( minWidth );
        widget->setMinimumHeight( minHeight );
        widget->setMaximumWidth( maxWidth );
        widget->setMaximumHeight( maxHeight );
        widget->resize( width, height );
        widget->move( x, y );
        if ( fullscreen ) {
            widget->showFullScreen();
        }
        if ( maximized ) {
            widget->showMaximized();
        }
        if ( fileDropEnabled ) {
            widget->setAcceptDrops( fileDropEnabled );
        }
        if ( center ) {
            widget->center();
        }
        if ( focus ) {
            widget->setFocus();
        }
        widget->webview->load( QUrl( url ) );
        if ( visible ) {
            widget->show();
        }
    }
}
