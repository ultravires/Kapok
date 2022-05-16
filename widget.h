#ifndef WIDGET_H
#define WIDGET_H

#include "webview.h"
#include <QMouseEvent>
#include <QWidget>

class QMouseEvent;

class Widget : public WebView {
    Q_OBJECT
  public:
    Widget( QWidget *parent = nullptr );

  protected:
    void mousePressEvent( QMouseEvent *event ) override;
    void mouseMoveEvent( QMouseEvent *event ) override;
    void mouseReleaseEvent( QMouseEvent *event ) override;

  private:
    bool   m_bDrag;
    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;

  signals:
};

#endif // WIDGET_H
