#include "webpage.h"

#include <QDir>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QWebEngineCertificateError>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>

WebPage::WebPage( QObject *parent )
    : QWebEnginePage( parent ) {}

WebPage::WebPage( QWebEngineProfile *profile, QObject *parent )
    : QWebEnginePage( profile, parent ) {
    setBackgroundColor( Qt::transparent );
    // https://doc.qt.io/qt-6/qwebenginepage.html#featurePermissionRequested
    connect( this, SIGNAL( featurePermissionRequested() ),
             SLOT( handleFeaturePermissionRequested() ) );
#if QT_VERSION >= QT_VERSION_CHECK( 6, 0, 0 )

    // https://doc.qt.io/qt-6/qwebenginepage.html#certificateError
    connect(
        this, SIGNAL( certificateError( const QWebEngineCertificateError ) ),
        SLOT( handleCertificateError( const QWebEngineCertificateError ) ) );
#endif
}

void WebPage::handleFeaturePermissionRequested(
    const QUrl &securityOrigin, QWebEnginePage::Feature feature ) {
    setFeaturePermission( securityOrigin, feature, PermissionGrantedByUser );
}

bool WebPage::handleCertificateError(
    const QWebEngineCertificateError &error ) {
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    qDebug( "%s %s %s", qPrintable( error.url().toString() ),
            qPrintable( tr( "Certificate Error" ) ),
            qPrintable( error.errorDescription() ) );
#else
    qDebug( "%s %s %s", qPrintable( error.url().toString() ),
            qPrintable( tr( "Certificate Error" ) ),
            qPrintable( error.description() ) );
#endif
    return true;
}

#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
// https://doc.qt.io/qt-5/qwebenginepage.html#certificateError
bool WebPage::certificateError( const QWebEngineCertificateError &error ) {
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    qDebug( "%s %s %s", qPrintable( error.url().toString() ),
            qPrintable( tr( "Certificate Error" ) ),
            qPrintable( error.errorDescription() ) );
#else
    qDebug( "%s %s %s", qPrintable( error.url().toString() ),
            qPrintable( tr( "Certificate Error" ) ),
            qPrintable( error.description() ) );
#endif
    return true;
}
#endif

WebPage::~WebPage() {}
