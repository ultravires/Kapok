#include "widget.h"
#include "jsbridge.h"
#include "webpage.h"
#include "webview.h"

#include <QGridLayout>
#include <QJsonDocument>
#include <QWebChannel>
#include <QWebEngineSettings>
#include <QWebEngineView>

Widget::Widget( QWidget *parent )
    : BaseWindow( parent ) {
    setSupportStretch( true );
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

void Widget::initTitleBar() {
    // 设置标题栏跑马灯效果，可以不设置;
    //    m_titleBar->setTitleRoll();
    m_titleBar->setBackgroundColor( 255, 255, 255, true );
    m_titleBar->setTitleIcon( ":/icons/window/close.png" );
    m_titleBar->setTitleContent( QStringLiteral( "即时通讯" ) );
    m_titleBar->setButtonType( MIN_MAX_BUTTON );
    m_titleBar->setTitleWidth( this->width() );
    // 控件置于顶层
    m_titleBar->raise();
}

Widget::~Widget() {}
