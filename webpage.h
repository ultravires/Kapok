#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QNetworkReply>
#include <QWebEnginePage>

class WebPage : public QWebEnginePage {
    Q_OBJECT
  public:
    explicit WebPage( QObject *parent = nullptr );
    ~WebPage();
    WebPage( QWebEngineProfile *profile, QObject *parent = nullptr );

  public slots:
    void handleFeaturePermissionRequested( const QUrl &securityOrigin,
                                           QWebEnginePage::Feature feature );
    bool handleCertificateError( const QWebEngineCertificateError &error );

  public:
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    bool certificateError( const QWebEngineCertificateError &error ) override;
#endif
};

#endif // WEBPAGE_H
