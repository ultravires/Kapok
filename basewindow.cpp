#include "basewindow.h"
#include <QApplication>
#include <QFile>
#include <QGridLayout>
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
    setAttribute( Qt::WA_DeleteOnClose );
    //        setAttribute( Qt::WA_InputMethodEnabled );
    //    setAttribute( Qt::WA_KeyCompression );
    //    setFocusPolicy( Qt::WheelFocus );
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

bool BaseWindow::isResizable() { return this->m_resizable; }

void BaseWindow::setResizable( bool resizable ) {
    this->m_resizable = resizable;
}

void BaseWindow::resizeEvent( QResizeEvent *event ) {
    if ( this->isResizable() ) {
        event->accept();
    } else {
        event->ignore();
    }
}

void BaseWindow::closeEvent( QCloseEvent *event ) { event->accept(); }

BaseWindow::~BaseWindow() {}
