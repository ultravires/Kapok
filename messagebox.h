#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "basewindow.h"
#include <QMessageBox>
#include <QWidget>

class MessageBox : BaseWindow {
    Q_OBJECT
  public:
    MessageBox( QWidget *parent = nullptr );
    ~MessageBox();

  public:
    int static success();
    int static warning();
    int static info();
    int static error();
};

#endif // MESSAGEBOX_H
