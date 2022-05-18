#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QEvent>
#include <QWebEngineView>

class WebView : public QWebEngineView {
    Q_OBJECT
  public:
    explicit WebView( QWidget *parent = nullptr );
    ~WebView();

  protected:
    bool            event( QEvent *event ) override;
    QWebEngineView *createWindow( QWebEnginePage::WebWindowType type ) override;

  private slots:
    void onRenderProcessTerminated(
        QWebEnginePage::RenderProcessTerminationStatus, int );
};

#endif // WEBVIEW_H
