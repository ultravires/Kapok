#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QObject>

class Directory {
  public:
    Directory();
    ~Directory();
    QStringList appConfigDir();
    QStringList audioDir();
    QStringList configDir();
    QStringList downloadDir();
    QStringList desktopDir();
    QStringList documentDir();
    QStringList homeDir();
    QStringList videoDir();
    QStringList pictureDir();
    QStringList tempDir();
    QStringList cacheDir();
};

#endif // DIRECTORY_H
