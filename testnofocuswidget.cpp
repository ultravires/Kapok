#include "testnofocuswidget.h"

TestNoFocusWidget::TestNoFocusWidget( QWidget *parent )
    : BaseWindow( parent ) {
    // 初始化标题栏;
    initTitleBar();
    this->show();
}

TestNoFocusWidget::~TestNoFocusWidget() {}

void TestNoFocusWidget::initTitleBar() {
    // 设置标题栏跑马灯效果，可以不设置;
    m_titleBar->setTitleRoll();
    m_titleBar->setBackgroundColor( 255, 255, 255, true );
    m_titleBar->setTitleIcon( ":/Resources/titleicon.png" );
    m_titleBar->setTitleContent(
        QStringLiteral( "前行中的小猪-前行之路还需前行" ) );
    m_titleBar->setButtonType( MIN_MAX_BUTTON );
    m_titleBar->setTitleWidth( this->width() );
}
