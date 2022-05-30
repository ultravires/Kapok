#include "webpage.h"

#include <QDir>
#include <QMessageBox>
#include <QWebEngineCertificateError>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>

WebPage::WebPage( QObject *parent )
    : QWebEnginePage( parent ) {
    qDebug( "Create a WebPage" );
    connect( this, SIGNAL( loadStarted() ), this, SLOT( on_loadStarted() ) );
}

void WebPage::on_loadStarted() {
    QFile apiFile(
        ":/qtwebchannel/qwebchannel.js" ); // load the API from the resources
    if ( !apiFile.open( QIODevice::ReadOnly ) )
        qDebug() << "Couldn't load Qt's QWebChannel API!";
    QString apiScript = QString::fromLocal8Bit( apiFile.readAll() );
    apiFile.close();

    this->runJavaScript( apiScript );

    QFile coreScriptFile( ":/scripts/core.js" );
    if ( !coreScriptFile.open( QIODevice::ReadOnly ) )
        qDebug() << "Couldn't load Qt's core script!";
    QString coreScript = QString::fromLocal8Bit( coreScriptFile.readAll() );
    coreScriptFile.close();
    this->runJavaScript( coreScript );

    //    QString script = QString::fromLatin1(
    //        "new QWebChannel(window.qt.webChannelTransport, (channel) => {"
    //        "window.__QT_CHANNEL__ = channel;"
    //        "})" );
    //    this->runJavaScript( script );

    //    QWebEngineScript script;
    //    QString          name = "invoke_qwebchannel_script";
    //    QString          s =
    //        QString::fromLatin1( "(function() {"
    //                             "    script =
    //                             document.createElement('script');" "
    //                             script.id = '%1';" "
    //                             document.head.appendChild(script);" "
    //                             script.innerText = `%2`;"
    //                             "})()" )
    //            .arg( name )
    //            .arg( apiScript );
    //    this->runJavaScript( s, QWebEngineScript::ApplicationWorld );
    //    script.setName( name );
    //    script.setSourceCode( s );
    //    script.setInjectionPoint( QWebEngineScript::DocumentReady );
    //    script.setRunsOnSubFrames( true );
    //    script.setWorldId( QWebEngineScript::ApplicationWorld );
    //    this->scripts().insert( script );
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
