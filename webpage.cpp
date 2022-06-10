#include "webpage.h"

#include <QDir>
#include <QMessageBox>
#include <QWebEngineCertificateError>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>

WebPage::WebPage( QObject *parent )
    : QWebEnginePage( parent ) {
    connect( this, SIGNAL( loadStarted() ), this, SLOT( loadStarted() ) );
}

void WebPage::loadStarted() {
    QFile coreScriptFile( ":/scripts/core.js" );
    if ( !coreScriptFile.open( QIODevice::ReadOnly ) )
        qDebug() << "Couldn't load Qt's core script!";
    QString coreScript = QString::fromLocal8Bit( coreScriptFile.readAll() );
    coreScriptFile.close();
    this->runJavaScript( coreScript );
}

WebPage::WebPage( QWebEngineProfile *profile, QObject *parent )
    : QWebEnginePage( profile, parent ) {
    connect( this, &QWebEnginePage::featurePermissionRequested, this,
             &WebPage::handleFeaturePermissionRequested );
}

void WebPage::handleFeaturePermissionRequested(
    const QUrl &securityOrigin, QWebEnginePage::Feature feature ) {
    setFeaturePermission( securityOrigin, feature, PermissionGrantedByUser );
}

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

WebPage::~WebPage() {}
