#include "directory.h"

#include <QStandardPaths>

Directory::Directory() {}

QStringList Directory::appConfigDir() {
    return QStandardPaths::standardLocations(
        QStandardPaths::AppConfigLocation );
}

QStringList Directory::audioDir() {
    return QStandardPaths::standardLocations( QStandardPaths::MusicLocation );
}

QStringList Directory::configDir() {
    return QStandardPaths::standardLocations( QStandardPaths::ConfigLocation );
}

QStringList Directory::downloadDir() {
    return QStandardPaths::standardLocations(
        QStandardPaths::DownloadLocation );
}

QStringList Directory::desktopDir() {
    return QStandardPaths::standardLocations( QStandardPaths::DesktopLocation );
}

QStringList Directory::documentDir() {
    return QStandardPaths::standardLocations(
        QStandardPaths::DocumentsLocation );
}

QStringList Directory::homeDir() {
    return QStandardPaths::standardLocations( QStandardPaths::HomeLocation );
}

QStringList Directory::videoDir() {
    return QStandardPaths::standardLocations( QStandardPaths::MoviesLocation );
}

QStringList Directory::pictureDir() {
    return QStandardPaths::standardLocations(
        QStandardPaths::PicturesLocation );
}

QStringList Directory::tempDir() {
    return QStandardPaths::standardLocations( QStandardPaths::TempLocation );
}

QStringList Directory::cacheDir() {
    return QStandardPaths::standardLocations( QStandardPaths::CacheLocation );
}

Directory::~Directory() {}
