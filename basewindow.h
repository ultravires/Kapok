#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMouseEvent>
#include <QWidget>

class QMouseEvent;

class BaseWindow : public QWidget {
    Q_OBJECT

  public:
    BaseWindow( QWidget *parent = nullptr );
    ~BaseWindow();
    void center();

  protected:
    void showEvent( QShowEvent *event ) override;
    void mousePressEvent( QMouseEvent *event ) override;
    void mouseMoveEvent( QMouseEvent *event ) override;
    void mouseReleaseEvent( QMouseEvent *event ) override;
    bool event( QEvent *event ) override;
};

#endif // BASEWINDOW_H
