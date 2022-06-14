#include "global.h"
#include "httplistener.h"
#include "mainwindow.h"
#include "requestmapper.h"
#include "webpage.h"
#include "webview.h"
#include "widget.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QLocale>
#include <QSettings>
#include <QTranslator>

using namespace stefanfrings;

int main( int argc, char *argv[] ) {

    qputenv( "QTWEBENGINE_CHROMIUM_FLAGS", "--no-sandbox" );

    QApplication app( argc, argv );
    app.setApplicationName( "Kapok" );
    app.setOrganizationName( "Programming enthusiast" );

    // i18n
    QTranslator       translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for ( const QString &locale : uiLanguages ) {
        const QString baseName = "Kapok_" + QLocale( locale ).name();
        if ( translator.load( ":/i18n/" + baseName ) ) {
            app.installTranslator( &translator );
            break;
        }
    }

    // Load the configuration file
    config                 = new Config();
    QString configFileName = config->getConfigFileName();

    // Configure logging
    QSettings *logSettings =
        new QSettings( configFileName, QSettings::IniFormat, &app );
    logSettings->beginGroup( "logging" );
    logger = new FileLogger( logSettings, 10000, &app );
    logger->installMsgHandler();

    // Log the library version
    qDebug( "QtWebApp has version %s", getQtWebAppLibVersion() );
    // Log the application version
    qDebug( "Kapok has version: %s", getKapokVersion() );

    // Session store
    QSettings *sessionSettings =
        new QSettings( configFileName, QSettings::IniFormat, &app );
    sessionSettings->beginGroup( "sessions" );
    sessionStore = new HttpSessionStore( sessionSettings, &app );

    // Static file controller
    QSettings *fileSettings =
        new QSettings( configFileName, QSettings::IniFormat, &app );
    fileSettings->beginGroup( "files" );
    staticFileController = new StaticFileController( fileSettings, &app );

    // HTTP server
    QSettings *listenerSettings =
        new QSettings( configFileName, QSettings::IniFormat, &app );
    listenerSettings->beginGroup( "listener" );
    new HttpListener( listenerSettings, new RequestMapper( &app ), &app );

    // Remote server
    QSettings *serverSettings =
        new QSettings( configFileName, QSettings::IniFormat, &app );
    serverSettings->beginGroup( "server" );
    QString url = serverSettings->value( "url" ).toString();

    qputenv( "QTWEBENGINE_REMOTE_DEBUGGING", "7777" );

    QUrl defaultURL;
    if ( url.trimmed().isEmpty() ) {
        defaultURL = QUrl( "http://127.0.0.1:8080/" );
    } else {
        defaultURL = QUrl( url.trimmed() );
    }

    Widget *widget = new Widget();
    widget->webview->load( defaultURL );
    widget->resize( 900, 600 );
    widget->show();

    return app.exec();
}
