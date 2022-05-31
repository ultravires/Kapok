#ifndef WIDGETCONTEXT_H
#define WIDGETCONTEXT_H

#include "widget.h"

class WidgetContext {
  public:
    static WidgetContext *instance();
    static void           addWidget( QString label, Widget *widget );
    static void           removeWidget( QString label );
    static Widget        *getWidget( QString label );
    static void           clear();

  private:
    WidgetContext();
    ~WidgetContext();
};

#endif // WIDGETCONTEXT_H
