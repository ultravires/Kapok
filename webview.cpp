#include "webview.h"

#include <QMenu>
#include <QTimer>
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineSettings>

WebView::WebView( QWidget *parent )
    : QWebEngineView( parent ) {

    connect( this, SIGNAL( loadStarted() ), this, SLOT( on_loadStarted() ) );

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
    this->settings()->setAttribute( QWebEngineSettings::LocalStorageEnabled,
                                    true );
    this->settings()->setAttribute(
        QWebEngineSettings::FullScreenSupportEnabled, true );
    // see also:
    // https://doc.qt.io/qt-6/qtwebengine-features.html#pepper-plugin-api
    this->settings()->setAttribute( QWebEngineSettings::PluginsEnabled, true );
    this->settings()->setAttribute( QWebEngineSettings::ErrorPageEnabled,
                                    true );
    this->settings()->setAttribute(
        QWebEngineSettings::LocalContentCanAccessRemoteUrls, true );
    this->settings()->setAttribute(
        QWebEngineSettings::JavascriptCanAccessClipboard, true );
    this->settings()->setAttribute( QWebEngineSettings::JavascriptCanPaste,
                                    true );
    this->settings()->setAttribute(
        QWebEngineSettings::AllowRunningInsecureContent, true );
    this->settings()->setAttribute(
        QWebEngineSettings::AllowWindowActivationFromJavaScript, true );
    this->settings()->setAttribute( QWebEngineSettings::JavascriptCanPaste,
                                    true );
    this->settings()->setAttribute( QWebEngineSettings::ScrollAnimatorEnabled,
                                    true );
    this->settings()->setAttribute( QWebEngineSettings::ScreenCaptureEnabled,
                                    true );
    this->settings()->setUnknownUrlSchemePolicy(
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

void WebView::on_loadStarted() { qDebug( "webView loadStarted" ); }

WebView::~WebView() {}
