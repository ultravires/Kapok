#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>

class WebView : public QWebEngineView {
    Q_OBJECT
  public:
    explicit WebView( QWidget *parent = nullptr );
};

#endif // WEBVIEW_H
