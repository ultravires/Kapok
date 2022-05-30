#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>

class QMouseEvent;

class BaseWindow : public QWidget {
    Q_OBJECT

  public:
    BaseWindow( QWidget *parent = nullptr );
    ~BaseWindow();
    void center();
};

#endif // BASEWINDOW_H
