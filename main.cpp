#include "global.h"
#include "httplistener.h"
#include "mainwindow.h"
#include "requestmapper.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QLocale>
#include <QSettings>
#include <QTranslator>

using namespace stefanfrings;

/**
 * Search the configuration file.
 * Aborts the application if not found.
 * @return The valid filename
 */
QString searchConfigFile() {
    QString appName = QCoreApplication::applicationName();
    QFile   file;
    file.setFileName( QDir::homePath() + "/.config/" + appName +
                      "/etc/Config.ini" );
    QString configFileName = QDir( file.fileName() ).canonicalPath();
    qDebug( "using config file %s", qPrintable( configFileName ) );
    if ( file.exists() ) {
        QString configFileName = QDir( file.fileName() ).canonicalPath();
        qDebug( "using config file %s", qPrintable( configFileName ) );
        return configFileName;
    }
    return "";
}

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

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
    QString configFileName = searchConfigFile();

    // Configure logging
    QSettings *logSettings =
        new QSettings( configFileName, QSettings::IniFormat, &app );
    logSettings->beginGroup( "logging" );
    logger = new FileLogger( logSettings, 10000, &app );
    logger->installMsgHandler();

    // Log the library version
    qDebug( "QtWebApp has version %s", getQtWebAppLibVersion() );

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

    qputenv( "QTWEBENGINE_REMOTE_DEBUGGING", "7777" );

    MainWindow w;
    w.show();
    return app.exec();
}
