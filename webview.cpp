#include "webview.h"

#include <QTimer>
#include <QWebEngineProfile>
#include <QWebEngineSettings>

WebView::WebView( QWidget *parent )
    : QWebEngineView( parent ) {
    this->page()->profile()->setHttpUserAgent( "QT netiler" );
    this->page()->profile()->setHttpCacheType(
        QWebEngineProfile::MemoryHttpCache );
    this->settings()->setAttribute( QWebEngineSettings::LocalStorageEnabled,
                                    true );
    this->settings()->setAttribute(
        QWebEngineSettings::FullScreenSupportEnabled, true );
    this->settings()->setAttribute( QWebEngineSettings::PluginsEnabled, true );
    this->settings()->setAttribute( QWebEngineSettings::ErrorPageEnabled,
                                    false );
    this->settings()->setAttribute(
        QWebEngineSettings::LocalContentCanAccessRemoteUrls, true );
    this->settings()->setAttribute(
        QWebEngineSettings::JavascriptCanAccessClipboard, true );
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

    connect( this,
             SIGNAL( renderProcessTerminated(
                 QWebEnginePage::RenderProcessTerminationStatus, int ) ),
             this,
             SLOT( onRenderProcessTerminated(
                 QWebEnginePage::RenderProcessTerminationStatus, int ) ) );
}

void WebView::onRenderProcessTerminated(
    QWebEnginePage::RenderProcessTerminationStatus, int ) {
    QTimer::singleShot( 100, [ this ] { this->reload(); } );
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

WebView::~WebView() {}
