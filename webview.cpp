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
    connect( this, SIGNAL( loadFinished( bool ) ), this,
             SLOT( on_loadFinished( bool ) ) );
    this->setContextMenuPolicy( Qt::NoContextMenu );
    this->page()->profile()->setHttpUserAgent( "QT netiler" );
    this->page()->profile()->setHttpCacheType(
        QWebEngineProfile::MemoryHttpCache );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::LocalStorageEnabled, true );
    this->page()->settings()->setAttribute(
        QWebEngineSettings::FullScreenSupportEnabled, true );
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

WebView::~WebView() {}
