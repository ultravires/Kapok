#ifndef TESTNOFOCUSWIDGET_H
#define TESTNOFOCUSWIDGET_H

#include "basewindow.h"
#include <QWidget>

class TestNoFocusWidget : BaseWindow {
  public:
    TestNoFocusWidget( QWidget *parent );
    ~TestNoFocusWidget();
    void initTitleBar();
};

#endif // TESTNOFOCUSWIDGET_H
