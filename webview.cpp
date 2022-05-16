#include "webview.h"

#include <QWebEngineProfile>
#include <QWebEngineSettings>

WebView::WebView( QWidget *parent )
    : QWebEngineView( parent ) {
    this->page()->profile()->setHttpUserAgent( "QT netiler" );
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
}
