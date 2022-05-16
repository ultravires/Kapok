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
    : WebView{ parent } {
    setAttribute( Qt::WA_QuitOnClose, true );
    // 设置窗口背景透明
    setAttribute( Qt::WA_TranslucentBackground, true );
    setStyleSheet( "background-color:transparent" );
    setAutoFillBackground( false );
    setContentsMargins( 0, 0, 0, 0 );

    JSBridge    *bridge     = new JSBridge( this );
    QWebChannel *webChannel = new QWebChannel();
    webChannel->registerObject( "bridge", bridge );

    WebPage *webPage = new WebPage( this );
    setPage( webPage );
    page()->setWebChannel( webChannel );

    QGridLayout *mainLayout = new QGridLayout( this );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( this );
}

//拖拽操作
void Widget::mousePressEvent( QMouseEvent *event ) {
    qDebug( "mousePressEvent" );
    // 如果是鼠标左键按下
    if ( event->button() == Qt::LeftButton ) {
        m_bDrag = true;
        //获得鼠标的初始位置
        mouseStartPoint = event->pos();
        //获得窗口的初始位置
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void Widget::mouseMoveEvent( QMouseEvent *event ) {
    qDebug( "mouseMoveEvent" );
    if ( m_bDrag ) {
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
        //获得鼠标移动的距离
        QPoint distance = event->globalPos() - mouseStartPoint;
#else
        QPoint distance = event->globalPosition().toPoint() - mouseStartPoint;
#endif
        //改变窗口的位置
        move( windowTopLeftPoint + distance );
    }
}

void Widget::mouseReleaseEvent( QMouseEvent *event ) {
    qDebug( "mouseReleaseEvent" );
    if ( event->button() == Qt::LeftButton ) {
        m_bDrag = false;
    }
}
