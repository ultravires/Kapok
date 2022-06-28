#include "webview.h"

#include <QFile>
#include <QMenu>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineSettings>

WebView::WebView( QWidget *parent )
    : QWebEngineView( parent ) {
    setWindowFlag( Qt::FramelessWindowHint );
    setAttribute( Qt::WA_TranslucentBackground );
    setAttribute( Qt::WA_QuitOnClose );
    setStyleSheet( "background-color: transparent;" );

    connect( this, SIGNAL( loadFinished( bool ) ), this,
             SLOT( on_loadFinished( bool ) ) );

    // https://doc.qt.io/qt-5/qt.html#ContextMenuPolicy-enum
    this->setContextMenuPolicy( Qt::NoContextMenu );
    //    this->setContextMenuPolicy( Qt::CustomContextMenu );
    //    connect( this, SIGNAL( customContextMenuRequested( QPoint ) ), this,
    //             SLOT( onCustomContextMenuRequested( QPoint ) ) );

    // https://doc.qt.io/qt-6/qwebengineprofile.html
    // https://doc.qt.io/qt-5/qwebengineprofile.html
    this->page()->profile()->setHttpUserAgent( "QT netiler" );
    this->page()->profile()->setHttpCacheType(
        QWebEngineProfile::MemoryHttpCache );

    // https://doc.qt.io/qt-6/qwebenginesettings.html#WebAttribute-enum
    // https://doc.qt.io/qt-5/qwebenginesettings.html#WebAttribute-enum
    this->page()->settings()->setAttribute(
        QWebEngineSettings::LocalStorageEnabled, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::FullScreenSupportEnabled, true );
    // see also:
    // https://doc.qt.io/qt-6/qtwebengine-features.html#pepper-plugin-api
    this->page()->settings()->setAttribute( QWebEngineSettings::PluginsEnabled,
                                            true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::ErrorPageEnabled, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::LocalContentCanAccessRemoteUrls, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::JavascriptCanAccessClipboard, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::JavascriptCanPaste, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::AllowRunningInsecureContent, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::AllowWindowActivationFromJavaScript, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::ScrollAnimatorEnabled, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::ScreenCaptureEnabled, true );
    this->page()->settings()->setUnknownUrlSchemePolicy(
        QWebEngineSettings::AllowAllUnknownUrlSchemes );
}

QWebEngineView *WebView::createWindow( QWebEnginePage::WebWindowType type ) {
    switch ( type ) {
    case QWebEnginePage::WebBrowserWindow:
        break;
    case QWebEnginePage::WebBrowserTab:
        break;
    case QWebEnginePage::WebBrowserBackgroundTab:
        break;
    case QWebEnginePage::WebDialog:
        break;
    default:
        break;
    }
    return this;
}

void WebView::contextMenuEvent( QContextMenuEvent * ) {}

void WebView::onCustomContextMenuRequested( QPoint ) {}

void WebView::on_loadFinished( bool finished ) {
    if ( finished ) {
        QFile coreScriptFile( ":/scripts/core.js" );
        if ( !coreScriptFile.open( QIODevice::ReadOnly ) )
            qDebug() << "Couldn't load Qt's core script!";
        QString coreScript = QString::fromLocal8Bit( coreScriptFile.readAll() );
        coreScriptFile.close();
        this->page()->runJavaScript( coreScript );
    }
}

void WebView::paintEvent( QPaintEvent *event ) {
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setBrush( QBrush( Qt::transparent ) );
    painter.setPen( Qt::transparent );
    QRect rect = this->rect();
    rect.setWidth( rect.width() - 1 );
    rect.setHeight( rect.height() - 1 );
    painter.drawRoundedRect( rect, 15, 15 );
    event->accept();
    QWidget::paintEvent( event );
}

WebView::~WebView() {}
