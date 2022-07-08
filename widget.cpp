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
    //    this->webview->page()->setBackgroundColor( Qt::transparent );
    this->webview->page()->setWebChannel( webChannel );

    QGridLayout *mainLayout = new QGridLayout( this );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( this->webview );
}

void Widget::closeEvent( QCloseEvent *event ) {
    QString label = property( "__label__" ).toString();
    qDebug( "Widget %s closed.", qPrintable( label ) );
    WidgetContext::removeWidget( label );
    this->webview->close();
}

Widget::~Widget() {
    emit webview->page()->webChannel()->destroyed();
    emit webview->page()->destroyed();
    emit webview->destroyed();
    delete webview;
}
