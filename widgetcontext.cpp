#include "widgetcontext.h"

#include <QMap>

static QMap<QString, Widget *> map;

WidgetContext::WidgetContext() {}

void WidgetContext::addWidget( QString label, Widget *widget ) {
    map.insert( label, widget );
}

void WidgetContext::removeWidget( QString label ) {
    QMap<QString, Widget *>::iterator it = map.find( label );
    if ( it != map.end() ) {
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

WidgetContext::~WidgetContext() {}
