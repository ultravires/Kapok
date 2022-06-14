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
    JSBridge    *bridge     = new JSBridge( this );
    QWebChannel *webChannel = new QWebChannel();
    webChannel->registerObject( "bridge", bridge );

    WebPage *webPage = new WebPage();
    this->webview->setPage( webPage );
    this->webview->page()->setWebChannel( webChannel );

    QGridLayout *mainLayout = new QGridLayout( this );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( this->webview );
}

void Widget::enterEvent( QEnterEvent *event ) { event->accept(); }

void Widget::leaveEvent( QEvent *event ) { event->accept(); }

void Widget::closeEvent( QCloseEvent *event ) {
    WidgetContext::removeWidget( property( "__label__" ).toString() );
    this->webview->close();
    event->accept();
}

Widget::~Widget() { delete webview; }
