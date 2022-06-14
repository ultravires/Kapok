#ifndef WIDGET_H
#define WIDGET_H

#include "basewindow.h"
#include "webview.h"
#include <QCloseEvent>
#include <QEnterEvent>
#include <QMouseEvent>
#include <QWidget>

class QCloseEvent;
class QEnterEvent;
class QMouseEvent;

class Widget : public BaseWindow {
    Q_OBJECT
  public:
    Widget( QWidget *parent = nullptr );
    ~Widget();

  public:
    WebView *webview = new WebView( this );

  protected:
    void enterEvent( QEnterEvent *event ) override;
    void leaveEvent( QEvent *event ) override;
    void closeEvent( QCloseEvent *event ) override;
};

#endif // WIDGET_H
