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
    //    setAttribute( Qt::WA_InputMethodEnabled, true );
    //    setAttribute( Qt::WA_KeyCompression, true );
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

BaseWindow::~BaseWindow() {}
