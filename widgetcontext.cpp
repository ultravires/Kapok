#include "widgetcontext.h"

#include <QMap>

static QMap<QString, Widget *> map;

WidgetContext::WidgetContext() {}

void WidgetContext::addWidget( QString label, Widget *widget ) {
    map.insert( label, widget );
}

void WidgetContext::removeWidget( QString label ) {
    QMap<QString, Widget *>::iterator it  = map.find( label );
    QMap<QString, Widget *>::iterator end = map.end();
    if ( it != end ) {
        map.erase( it );
    }
}

Widget *WidgetContext::getWidget( QString label ) {
    if ( map.contains( label ) ) {
        QMap<QString, Widget *>::iterator it = map.find( label );
        return it.value();
    }
    return nullptr;
}

void WidgetContext::clear() { map.clear(); }

void WidgetContext::closeAllWidget() {
    QMap<QString, Widget *>::const_iterator it  = map.constBegin();
    QMap<QString, Widget *>::const_iterator end = map.constEnd();
    while ( it != end ) {
        Widget *widget = it.value();
        if ( widget ) {
            widget->close();
        }
        it++;
    }
    clear();
}

WidgetContext::~WidgetContext() {}
