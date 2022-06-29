#include "basewindow.h"
#include <QApplication>
#include <QPainter>
#include <QPainterPath>
#include <QScreen>

#define STRETCH_RECT_HEIGHT 4 // 拉伸小矩形的高度;
#define STRETCH_RECT_WIDTH 4  // 拉伸小矩形的宽度;

BaseWindow::BaseWindow( QWidget *parent )
    : QWidget( parent ) {
    setWindowFlag( Qt::Widget );
    setWindowFlag( Qt::FramelessWindowHint );
    setAttribute( Qt::WA_TranslucentBackground );
    //    setAttribute( Qt::WA_OpaquePaintEvent );
    //    setAttribute( Qt::WA_NoSystemBackground );
    setAttribute( Qt::WA_DeleteOnClose );
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
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setBrush( QBrush( Qt::transparent ) );
    painter.setPen( Qt::transparent );
    QRect rect = this->rect();
    rect.setWidth( rect.width() - 1 );
    rect.setHeight( rect.height() - 1 );
    painter.drawRoundedRect( rect, 15, 15 );
    QWidget::paintEvent( event );
}

void BaseWindow::resizeEvent( QResizeEvent *event ) {
    // TODO
}

void BaseWindow::closeEvent( QCloseEvent *event ) { event->accept(); }

BaseWindow::~BaseWindow() {}
