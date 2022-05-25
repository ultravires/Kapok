#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QContextMenuEvent>
#include <QEvent>
#include <QWebEngineView>

class WebView : public QWebEngineView {
    Q_OBJECT
  public:
    explicit WebView( QWidget *parent = nullptr );
    ~WebView();

  protected:
    QWebEngineView *createWindow( QWebEnginePage::WebWindowType type ) override;
    void            contextMenuEvent( QContextMenuEvent            *) override;

  private slots:
    void onCustomContextMenuRequested( QPoint );
    void on_loadStarted();
};

#endif // WEBVIEW_H
