#include "downloadmanager.h"
#include "database.h"
#include "directory.h"

#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonObject>
#include <QNetworkReply>
#include <QTextStream>
#include <QTimer>

#include <cstdio>

using namespace std;

DownloadManager::DownloadManager( QObject *parent )
    : QObject( parent ) {}

void DownloadManager::append( const QStringList &urls ) {
    for ( const QString &urlAsString : urls )
        append( QUrl::fromEncoded( urlAsString.toLocal8Bit() ) );

    if ( downloadQueue.isEmpty() ) {
        QTimer::singleShot( 0, this, &DownloadManager::finished );
    }
}

void DownloadManager::append( const QUrl &url ) {
    if ( downloadQueue.isEmpty() ) {
        QTimer::singleShot( 0, this, &DownloadManager::startNextDownload );
    }

    downloadQueue.enqueue( url );
    ++totalCount;
}

QString DownloadManager::saveFileName( const QUrl &url, bool askForSavePath ) {
    Directory *directory   = new Directory();
    QString    downloadDir = directory->downloadDir().at( 0 );
    QString    path        = url.path();
    QString    basename    = downloadDir + "/" + QFileInfo( path ).fileName();

    if ( askForSavePath ) {
        basename = QFileDialog::getSaveFileName( QApplication::activeWindow(),
                                                 QStringLiteral( "另存为" ),
                                                 basename );
    } else {
        if ( basename.isEmpty() ) basename = "download";
    }

    if ( basename.isEmpty() ) {
        return "";
    }

    if ( QFile::exists( basename ) ) {
        // already exists, don't overwrite
        int i = 1;
        basename += "(";
        while ( QFile::exists( basename + QString::number( i ) ) )
            ++i;

        basename += QString::number( i );
        basename += ")";
    }
    return basename;
}

void DownloadManager::startNextDownload() {
    if ( downloadQueue.isEmpty() ) {
        printf( "%d/%d files downloaded successfully\n", downloadedCount,
                totalCount );
        emit finished();
        return;
    }

    QUrl url = downloadQueue.dequeue();

    QNetworkRequest request( url );
    currentDownload = manager.get( request );
    connect( currentDownload, &QNetworkReply::metaDataChanged, this,
             &DownloadManager::metaDataChanged );
    connect( currentDownload, &QNetworkReply::downloadProgress, this,
             &DownloadManager::downloadProgress );
    connect( currentDownload, &QNetworkReply::finished, this,
             &DownloadManager::downloadFinished );
    connect( currentDownload, &QNetworkReply::readyRead, this,
             &DownloadManager::downloadReadyRead );

    // prepare the output
    printf( "Downloading %s...\n", url.toEncoded().constData() );
    downloadTimer.start();
}

void DownloadManager::metaDataChanged() {
    QUrl     url = currentDownload->url();
    QString  filename;
    QVariant variant =
        currentDownload->header( QNetworkRequest::ContentDispositionHeader );
    if ( variant.isValid() ) {
        qDebug( "variant: %s", qPrintable( QByteArray::fromPercentEncoding(
                                               variant.toByteArray() )
                                               .constData() ) );
        QString contentDisposition =
            QByteArray::fromPercentEncoding( variant.toByteArray() )
                .constData();
        QRegularExpression      regExp( "(.*)filename=\"(?<filename>.*)\"" );
        QRegularExpressionMatch match = regExp.match( contentDisposition );
        if ( match.hasMatch() ) {
            filename = match.captured( "filename" );
        }

        if ( filename.isEmpty() ) {
            filename = "download";
        }

        Directory *directory   = new Directory();
        QString    downloadDir = directory->downloadDir().at( 0 );
        QString    path        = downloadDir + "/" + filename;

        if ( QFile::exists( path ) ) {
            // already exists, don't overwrite
            int i = 1;
            path += "(";
            while ( QFile::exists( path + QString::number( i ) ) )
                ++i;

            path += QString::number( i );
            path += ")";
        }

        qDebug( "file path = %s", qPrintable( path ) );

        output.setFileName( path );
        if ( !output.open( QIODevice::WriteOnly ) ) {
            fprintf( stderr,
                     "Problem opening save file '%s' for download '%s': %s\n",
                     qPrintable( path ), url.toEncoded().constData(),
                     qPrintable( output.errorString() ) );
            currentDownload->abort();
            startNextDownload();
            return; // skip this download
        }
    }
}

void DownloadManager::downloadProgress( qint64 bytesReceived,
                                        qint64 bytesTotal ) {

    emit progress( bytesReceived, bytesReceived );

    progressBar.setStatus( bytesReceived, bytesTotal );

    // calculate the download speed
    double  speed = bytesReceived * 1000.0 / downloadTimer.elapsed();
    QString unit;
    if ( speed < 1024 ) {
        unit = "bytes/sec";
    } else if ( speed < 1024 * 1024 ) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024 * 1024;
        unit = "MB/s";
    }

    progressBar.setMessage(
        QString::fromLatin1( "%1 %2" ).arg( speed, 3, 'f', 1 ).arg( unit ) );
    progressBar.update();
}

void DownloadManager::downloadFinished() {
    progressBar.clear();
    output.close();

    if ( currentDownload->error() ) {
        // download failed
        fprintf( stderr, "Failed: %s\n",
                 qPrintable( currentDownload->errorString() ) );
        output.remove();
    } else {
        // let's check if it was actually a redirect
        if ( isHttpRedirect() ) {
            reportRedirect();
            output.remove();
        } else {
            printf( "Succeeded.\n" );
            ++downloadedCount;
        }
    }

    currentDownload->deleteLater();
    startNextDownload();
}

void DownloadManager::downloadReadyRead() {
    output.write( currentDownload->readAll() );
}

bool DownloadManager::isHttpRedirect() const {
    int statusCode =
        currentDownload->attribute( QNetworkRequest::HttpStatusCodeAttribute )
            .toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303 ||
           statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void DownloadManager::reportRedirect() {
    int statusCode =
        currentDownload->attribute( QNetworkRequest::HttpStatusCodeAttribute )
            .toInt();
    QUrl requestUrl = currentDownload->request().url();
    QTextStream( stderr ) << "Request: " << requestUrl.toDisplayString()
                          << " was redirected with code: " << statusCode
                          << '\n';

    QVariant target = currentDownload->attribute(
        QNetworkRequest::RedirectionTargetAttribute );
    if ( !target.isValid() ) return;
    QUrl redirectUrl = target.toUrl();
    if ( redirectUrl.isRelative() )
        redirectUrl = requestUrl.resolved( redirectUrl );
    QTextStream( stderr ) << "Redirected to: " << redirectUrl.toDisplayString()
                          << '\n';
}
