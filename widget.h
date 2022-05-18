#ifndef WIDGET_H
#define WIDGET_H

#include "basewindow.h"
#include "webview.h"
#include <QMouseEvent>
#include <QWidget>

class QMouseEvent;

class Widget : public BaseWindow {
    Q_OBJECT
  public:
    Widget( QWidget *parent = nullptr );
    ~Widget();
    void initTitleBar();

  public:
    WebView *webview = new WebView( this );
  signals:
};

#endif // WIDGET_H
