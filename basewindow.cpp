#include "basewindow.h"
#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QPainterPath>
#include <QScreen>

#define STRETCH_RECT_HEIGHT 4 // 拉伸小矩形的高度;
#define STRETCH_RECT_WIDTH 4  // 拉伸小矩形的宽度;

BaseWindow::BaseWindow( QWidget *parent )
    : QWidget( parent ) {
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint |
                    Qt::WindowMinimizeButtonHint );
    setAttribute( Qt::WA_TranslucentBackground, true );
    setStyleSheet( "background-color:transparent" );
    setAutoFillBackground( false );
    setAttribute( Qt::WA_DeleteOnClose, true );
}

void BaseWindow::showEvent( QShowEvent *event ) {
    return QWidget::showEvent( event );
}

void BaseWindow::center() {
    int clientWidth     = this->width();
    int clientHeight    = this->height();
    int availableWidth  = this->screen()->availableSize().width();
    int availableHeight = this->screen()->availableSize().height();
    int left            = ( availableWidth - clientWidth ) / 2;
    int top             = ( availableHeight - clientHeight ) / 2;
    this->move( left, top );
}

void BaseWindow::mouseMoveEvent( QMouseEvent *event ) {
    return QWidget::mouseMoveEvent( event );
}

void BaseWindow::mousePressEvent( QMouseEvent *event ) {
    return QWidget::mousePressEvent( event );
}

void BaseWindow::mouseReleaseEvent( QMouseEvent *event ) {
    return QWidget::mouseReleaseEvent( event );
}

bool BaseWindow::event( QEvent *event ) { return QWidget::event( event ); }

BaseWindow::~BaseWindow() {}
