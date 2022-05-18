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
    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint
    // 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint |
                    Qt::WindowMinimizeButtonHint );
    // 设置窗口背景透明
    setAttribute( Qt::WA_TranslucentBackground, true );
    setStyleSheet( "background-color:transparent" );
    setAutoFillBackground( false );

    // 注意！！！如果是主窗口不要设置WA_DeleteOnClose属性;
    // 关闭窗口时释放资源;
    setAttribute( Qt::WA_DeleteOnClose, true );
    // 初始化标题栏;
    initTitleBar();
}

void BaseWindow::initTitleBar() {
    m_titleBar = new TitleBar( this );
    m_titleBar->move( 0, 0 );

    connect( m_titleBar, SIGNAL( signalButtonMinClicked() ), this,
             SLOT( onButtonMinClicked() ) );
    connect( m_titleBar, SIGNAL( signalButtonRestoreClicked() ), this,
             SLOT( onButtonRestoreClicked() ) );
    connect( m_titleBar, SIGNAL( signalButtonMaxClicked() ), this,
             SLOT( onButtonMaxClicked() ) );
    connect( m_titleBar, SIGNAL( signalButtonCloseClicked() ), this,
             SLOT( onButtonCloseClicked() ) );
}

void BaseWindow::paintEvent( QPaintEvent *event ) {
    //设置背景色;
    QPainter     painter( this );
    QPainterPath pathBack;
    pathBack.setFillRule( Qt::WindingFill );
    pathBack.addRoundedRect( QRect( 0, 0, this->width(), this->height() ), 3,
                             3 );
    painter.setRenderHint( QPainter::SmoothPixmapTransform, true );
    painter.fillPath( pathBack, QBrush( QColor( 255, 255, 255 ) ) );

    return QWidget::paintEvent( event );
}

void BaseWindow::loadStyleSheet( const QString &sheetName ) {
    QFile file( ":/Resources/" + sheetName + ".css" );
    file.open( QFile::ReadOnly );
    if ( file.isOpen() ) {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String( file.readAll() );
        this->setStyleSheet( styleSheet );
    }
}

void BaseWindow::onButtonMinClicked() { showMinimized(); }

void BaseWindow::onButtonRestoreClicked() {
    QPoint windowPos;
    QSize  windowSize;
    m_titleBar->getRestoreInfo( windowPos, windowSize );
    this->setGeometry( QRect( windowPos, windowSize ) );
}

void BaseWindow::onButtonMaxClicked() {
    m_titleBar->saveRestoreInfo( this->pos(),
                                 QSize( this->width(), this->height() ) );
    QRect desktopRect = this->screen()->availableGeometry();
    QRect FactRect    = QRect( desktopRect.x() - 3, desktopRect.y() - 3,
                               desktopRect.width() + 6, desktopRect.height() + 6 );
    setGeometry( FactRect );
}

void BaseWindow::onButtonCloseClicked() { close(); }

void BaseWindow::calculateCurrentStrechRect() {
    // 四个角Rect;
    m_leftTopRect     = QRect( 0, 0, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT );
    m_leftBottomRect  = QRect( 0, this->height() - STRETCH_RECT_HEIGHT,
                               STRETCH_RECT_WIDTH, STRETCH_RECT_WIDTH );
    m_rightTopRect    = QRect( this->width() - STRETCH_RECT_WIDTH, 0,
                               STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT );
    m_rightBottomRect = QRect( this->width() - STRETCH_RECT_WIDTH,
                               this->height() - STRETCH_RECT_HEIGHT,
                               STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT );

    // 四条边Rect;
    m_topBorderRect =
        QRect( STRETCH_RECT_WIDTH, 0, this->width() - STRETCH_RECT_WIDTH * 2,
               STRETCH_RECT_HEIGHT );
    m_rightBorderRect =
        QRect( this->width() - STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT,
               STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT * 2 );
    m_bottomBorderRect =
        QRect( STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT,
               this->width() - STRETCH_RECT_WIDTH * 2, STRETCH_RECT_HEIGHT );
    m_leftBorderRect = QRect( 0, STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH,
                              this->height() - STRETCH_RECT_HEIGHT * 2 );
}

// 在窗口第一次show完之后需要计算拉伸区域Rect位置;
void BaseWindow::showEvent( QShowEvent *event ) {
    calculateCurrentStrechRect();
}

void BaseWindow::center() {
    int clientWidth     = this->width();
    int clientHeight    = this->height();
    int availableWidth  = this->screen()->availableSize().width();
    int availableHeight = this->screen()->availableSize().height();
    int left            = ( availableWidth - clientWidth ) / 2;
    int top             = ( availableHeight - clientHeight ) / 2;
    qDebug( "clientWidth: %d, clientHeight: %d, availableWidth: %d, "
            "availableHeight: %d",
            clientWidth, clientHeight, availableWidth, availableHeight );
    this->move( left, top );
}

BaseWindow::~BaseWindow() {}
