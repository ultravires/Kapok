#include "config.h"

#include <QApplication>
#include <QDir>
#include <QFile>

Config::Config( QString configFileName ) {
    QString dirPath = QApplication::applicationDirPath();
    QString appName = QApplication::applicationName();

    if ( !configFileName.isEmpty() ) {
        m_configFileName = configFileName;
    } else {
        m_configFileName = dirPath + "/etc/Config.ini";
    }

    QFile file;
    file.setFileName( m_configFileName );
    if ( !file.exists() ) {
        file.setFileName( QDir::homePath() + "/.config/" + appName +
                          "/etc/Config.ini" );
    }
    if ( file.exists() ) {
        QString configFileName = QDir( file.fileName() ).canonicalPath();
        qDebug( "using config file %s", qPrintable( configFileName ) );
    }
    file.close();
}

QString Config::getConfigFileName() { return m_configFileName; }

Config::~Config() {}
