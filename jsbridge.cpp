#include "jsbridge.h"
#include "messagebox.h"
#include "widget.h"
#include "widgetcontext.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScreen>
#include <QUrl>

JSBridge::JSBridge( QWidget *widget )
    : QObject() {
    this->m_widget = widget;
}

void JSBridge::message( const QString &title, const QString &text ) {
    MessageBox::message( m_widget, title, text );
}

bool JSBridge::ask( QString title, QString text ) {
    return MessageBox::ask( m_widget, title, text );
}

bool JSBridge::confirm( QString title, QString text ) {
    return MessageBox::confirm( m_widget, title, text );
}

void JSBridge::warning( QString title, QString message ) {
    QMessageBox::warning( m_widget, title, message );
}

void JSBridge::setFullScreen( bool isFullScreen ) {
    if ( isFullScreen ) {
        m_widget->showFullScreen();
    } else {
        m_widget->showNormal();
    }
}

void JSBridge::maximize() { m_widget->showMaximized(); }

void JSBridge::minimize() { m_widget->showMinimized(); }

void JSBridge::normal() { m_widget->showNormal(); }

void JSBridge::toggleMaximize() {
    if ( m_widget->isMaximized() ) {
        m_widget->showNormal();
    } else {
        m_widget->showMaximized();
    }
}

bool JSBridge::isMaximize() { return m_widget->isMaximized(); }

void JSBridge::center() {
    int clientWidth  = m_widget->width();
    int clientHeight = m_widget->height();
    int availableWidth =
        QApplication::primaryScreen()->availableGeometry().width();
    int availableHeight =
        QApplication::primaryScreen()->availableGeometry().height();
    int left = ( availableWidth - clientWidth ) / 2;
    int top  = ( availableHeight - clientHeight ) / 2;
    m_widget->move( left, top );
}

void JSBridge::move( int left, int top ) { m_widget->move( left, top ); }

void JSBridge::close() { m_widget->close(); }

void JSBridge::quit() {
    qApp->setQuitOnLastWindowClosed( true );
    qApp->closeAllWindows();
    qApp->exit();
}

void JSBridge::setDecorations( bool decorations ) {
    if ( decorations ) {
        m_widget->setWindowFlag( Qt::Window, true );
        m_widget->setWindowFlag( Qt::FramelessWindowHint, false );
        m_widget->show();
    } else {
        m_widget->setWindowFlag( Qt::Window, true );
        m_widget->setWindowFlag( Qt::FramelessWindowHint, true );
        m_widget->show();
    }
}

bool JSBridge::isDecorations() {
    return m_widget->windowFlags().testFlag( Qt::FramelessWindowHint );
}

void JSBridge::setTitle( QString title ) { m_widget->setWindowTitle( title ); }

void JSBridge::resize( int width, int height ) {
    m_widget->resize( width, height );
}

void JSBridge::show() { m_widget->show(); }

void JSBridge::setGeometry( int left, int top, int width, int height ) {
    m_widget->setGeometry( left, top, width, height );
}

void JSBridge::download( QString url ) {
    if ( url.isEmpty() ) {
        return;
    }
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
//      for*
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

QWidget *JSBridge::open( QString uniqueLabel, QString options ) {
    if ( uniqueLabel.isEmpty() ) {
        return nullptr;
    }
    Widget *w = WidgetContext::getWidget( uniqueLabel );
    if ( w != nullptr ) {
        w->show();
        w->activateWindow();
        return w;
    }
    Widget *widget = new Widget();
    WidgetContext::addWidget( uniqueLabel, widget );
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
        int width = this->m_widget->width();
        // 窗口的高度
        int height = this->m_widget->height();
        // 窗口的最小宽度
        int minWidth = this->m_widget->minimumWidth();
        // 窗口的最小高度
        int minHeight = this->m_widget->minimumHeight();
        // 窗口的最大宽度
        int maxWidth = this->m_widget->maximumWidth();
        // 窗口的最大高度
        int maxHeight = this->m_widget->maximumHeight();
        // 是否可改变窗口大小
        bool resizable = false;
        // 窗口标题
        QString title = this->m_widget->windowTitle();
        // 窗口是否全屏化
        bool fullscreen = this->m_widget->isFullScreen();
        // 窗口最初是隐藏还是聚焦
        bool focus = true;
        // 窗口是否透明
        bool transparent =
            this->m_widget->testAttribute( Qt::WA_TranslucentBackground );
        // 窗口是否最大化
        bool maximized = this->m_widget->isMaximized();
        // 窗口是否应在创建时立即可见
        bool visible = true;
        // 窗口是否具有默认边框和栏
        bool decorations =
            this->m_widget->windowFlags().testFlag( Qt::FramelessWindowHint );
        // 窗口图标是否在任务栏展示
        bool skipTaskbar = false;
        // 窗口是否置顶
        bool alwaysOnTop =
            this->m_widget->windowFlags().testFlag( Qt::WindowStaysOnTopHint );
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
        if ( jsonObject.contains( "resizable" ) ) {
            resizable = jsonObject.value( "resizable" ).toBool();
        }
        if ( jsonObject.contains( "skipTaskbar" ) ) {
            skipTaskbar = jsonObject.value( "skipTaskbar" ).toBool();
        }
        if ( decorations ) {
            widget->setWindowFlag( Qt::FramelessWindowHint, true );
        } else {
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
        widget->setResizable( resizable );
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
    return widget;
}
