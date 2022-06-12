#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>

class WebPage : public QWebEnginePage {
    Q_OBJECT
  public:
    explicit WebPage( QObject *parent = nullptr );
    ~WebPage();
    WebPage( QWebEngineProfile *profile, QObject *parent = nullptr );
    void handleFeaturePermissionRequested( const QUrl &securityOrigin,
                                           QWebEnginePage::Feature feature );

  protected:
    bool certificateError( const QWebEngineCertificateError &error );

  private slots:
    void loadStarted();
};

#endif // WEBPAGE_H
