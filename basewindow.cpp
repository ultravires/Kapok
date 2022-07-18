#include "basewindow.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QPainterPath>
#include <QScreen>

#define STRETCH_RECT_HEIGHT 4 // 拉伸小矩形的高度;
#define STRETCH_RECT_WIDTH 4  // 拉伸小矩形的宽度;
#define SHADOW_WIDTH 10       // 阴影边框宽度;

BaseWindow::BaseWindow( QWidget *parent )
    : QWidget( parent ) {
    setWindowFlag( Qt::Widget );
    setAttribute( Qt::WA_DeleteOnClose );

    QJsonObject jsonObject;
    jsonObject.insert( "decorations", false );
    jsonObject.insert( "transparent", true );
    if ( jsonObject.value( "decorations" ).toBool() == false ) {
        setWindowFlag( Qt::FramelessWindowHint );
        setWindowFlag( Qt::NoDropShadowWindowHint );
    }
    if ( jsonObject.value( "transparent" ).toBool() == true ) {
        setAttribute( Qt::WA_TranslucentBackground );
    }
}

void BaseWindow::center() {
    int clientWidth  = this->width();
    int clientHeight = this->height();
    int availableWidth =
        QApplication::primaryScreen()->availableGeometry().width();
    ;
    int availableHeight =
        QApplication::primaryScreen()->availableGeometry().height();
    ;
    int left = ( availableWidth - clientWidth ) / 2;
    int top  = ( availableHeight - clientHeight ) / 2;
    this->move( left, top );
}

void BaseWindow::setSize( int width, int height ) {
    this->resize( width, height );
}

bool BaseWindow::isResizable() { return this->m_resizable; }

void BaseWindow::setResizable( bool resizable ) {
    this->m_resizable = resizable;
}

void BaseWindow::paintEvent( QPaintEvent *event ) {
    // 窗口圆角
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setBrush( QBrush( Qt::transparent ) );
    painter.setPen( Qt::transparent );
    QRect rect = this->rect();
    rect.setWidth( rect.width() - 1 );
    rect.setHeight( rect.height() - 1 );
    painter.drawRoundedRect( rect, 15, 15 );

    // 窗口边框阴影
    QGraphicsDropShadowEffect *pEffect = new QGraphicsDropShadowEffect( this );
    pEffect->setOffset( 0, 0 );
    pEffect->setColor( QColor( QStringLiteral( "black" ) ) );
    pEffect->setBlurRadius( 30 );
    //    this->setGraphicsEffect( pEffect );
}

void BaseWindow::resizeEvent( QResizeEvent *event ) {
    // TODO
}

void BaseWindow::closeEvent( QCloseEvent *event ) { event->accept(); }

BaseWindow::~BaseWindow() {}
