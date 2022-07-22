#include "widget.h"
#include "jsbridge.h"
#include "webpage.h"
#include "webview.h"
#include "widgetcontext.h"

#include <QGridLayout>
#include <QJsonDocument>
#include <QWebChannel>
#include <QWebEngineSettings>
#include <QWebEngineView>

Widget::Widget( QWidget *parent )
    : BaseWindow( parent ) {
    WebPage *webPage = new WebPage();
    this->webview->setPage( webPage );
    this->webview->page()->setBackgroundColor( Qt::transparent );

    QWebChannel *webChannel = new QWebChannel();
    JSBridge    *bridge     = new JSBridge( this );
    webChannel->registerObject( "bridge", bridge );
    this->webview->page()->setWebChannel( webChannel );

    QGridLayout *mainLayout = new QGridLayout( this );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( this->webview );
}

void Widget::closeEvent( QCloseEvent *event ) {
    QString label = property( "__label__" ).toString();
    qDebug( "Widget %s closed.", qPrintable( label ) );
    WidgetContext::removeWidget( label );
}

Widget::~Widget() { delete webview; }
