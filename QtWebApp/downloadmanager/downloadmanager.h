#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include "textprogressbar.h"

#include <QElapsedTimer>
#include <QFile>
#include <QNetworkAccessManager>
#include <QObject>
#include <QQueue>

class DownloadManager : public QObject {
    Q_OBJECT

  public:
    explicit DownloadManager( QObject *parent = nullptr );

    void           append( const QUrl &url );
    void           append( const QStringList &urls );
    static QString saveFileName( const QUrl &url, bool askForSavePath = false );
    bool           askForSavePath = false;

  signals:
    void finished();
    void progress( qint64 bytesReceived, qint64 bytesTota );

  private slots:
    void startNextDownload();
    void downloadProgress( qint64 bytesReceived, qint64 bytesTotal );
    void downloadFinished();
    void metaDataChanged();
    void downloadReadyRead();

  private:
    bool isHttpRedirect() const;
    void reportRedirect();

    QNetworkAccessManager manager;
    QQueue<QUrl>          downloadQueue;
    QNetworkReply        *currentDownload = nullptr;
    QFile                 output;
    QElapsedTimer         downloadTimer;
    TextProgressBar       progressBar;

    int downloadedCount = 0;
    int totalCount      = 0;
};

#endif
