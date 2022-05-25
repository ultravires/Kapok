#include "messagebox.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QRect>
#include <QVBoxLayout>

void MessageBox::message( QWidget *parent, const QString &title,
                          const QString &text ) {
    MessageBox *messageBox = new MessageBox( parent );
    // 标题
    QLabel      *titleLabel  = new QLabel( title );
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget( titleLabel );
    // 内容
    QLabel      *textLabel     = new QLabel( text );
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addWidget( textLabel );
    // 按钮
    QPushButton *confirmButton = new QPushButton( tr( "Confirm" ) );
    connect( confirmButton, SIGNAL( clicked() ), messageBox,
             SLOT( onConfirmButtonClicked() ) );

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget( confirmButton );

    QVBoxLayout *mainLayout = new QVBoxLayout( messageBox );
    mainLayout->addLayout( titleLayout );
    mainLayout->addLayout( contentLayout );
    mainLayout->addLayout( buttonLayout );
    messageBox->show();
}

bool MessageBox::confirm( QWidget *parent, const QString &title,
                          const QString &text ) {
    MessageBox *messageBox = new MessageBox( parent );

    QLabel      *titleLabel  = new QLabel( title );
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget( titleLabel );

    QLabel      *textLabel     = new QLabel( text );
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addWidget( textLabel );

    QPushButton *cancelButton = new QPushButton( tr( "取消" ) );
    cancelButton->setFixedSize( 64, 32 );
    cancelButton->setStyleSheet(
        "background-color: #DBDCDE; border-radius: 4px; color: #fff" );
    connect( cancelButton, SIGNAL( clicked() ), messageBox,
             SLOT( onCancelButtonClicked() ) );
    QPushButton *confirmButton = new QPushButton( tr( "确定" ) );
    confirmButton->setFixedSize( 64, 32 );
    confirmButton->setStyleSheet(
        "background-color: #3180F6; border-radius: 4px; color: #fff" );
    connect( confirmButton, SIGNAL( clicked() ), messageBox,
             SLOT( onConfirmButtonClicked() ) );
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment( Qt::AlignRight );
    buttonLayout->addWidget( cancelButton );
    buttonLayout->addWidget( confirmButton );

    QVBoxLayout *mainLayout = new QVBoxLayout( messageBox );
    mainLayout->setContentsMargins( 24, 20, 24, 20 );
    mainLayout->addLayout( titleLayout );
    mainLayout->addLayout( contentLayout );
    mainLayout->addLayout( buttonLayout );
    messageBox->show();
    messageBox->m_eventLoop->exec();
    return messageBox->m_chooseResult;
}

bool MessageBox::ask( QWidget *parent, const QString &title,
                      const QString &text ) {
    MessageBox *messageBox = new MessageBox( parent );

    QLabel      *titleLabel  = new QLabel( title );
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget( titleLabel );

    QLabel      *textLabel     = new QLabel( text );
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addWidget( textLabel );

    QPushButton *cancelButton = new QPushButton( tr( "No" ) );
    connect( cancelButton, SIGNAL( clicked() ), messageBox,
             SLOT( onCancelButtonClicked() ) );
    QPushButton *confirmButton = new QPushButton( tr( "Yes" ) );
    connect( confirmButton, SIGNAL( clicked() ), messageBox,
             SLOT( onConfirmButtonClicked() ) );
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget( cancelButton );
    buttonLayout->addWidget( confirmButton );

    QVBoxLayout *mainLayout = new QVBoxLayout( messageBox );
    mainLayout->addLayout( titleLayout );
    mainLayout->addLayout( contentLayout );
    mainLayout->addLayout( buttonLayout );
    messageBox->show();
    messageBox->m_eventLoop->exec();
    return messageBox->m_chooseResult;
}

MessageBox::MessageBox( QWidget *parent )
    : BaseWindow( parent ) {
    setWindowFlags( Qt::Dialog | Qt::FramelessWindowHint );
    setAttribute( Qt::WA_QuitOnClose, true );
    resize( 360, 160 );
}

void MessageBox::onCancelButtonClicked() {
    this->m_chooseResult = false;
    this->close();
}

void MessageBox::onConfirmButtonClicked() {
    this->m_chooseResult = true;
    this->close();
}

void MessageBox::paintEvent( QPaintEvent *event ) {
    QPainter     painter( this );
    QPainterPath pathBackground;
    pathBackground.setFillRule( Qt::WindingFill );
    pathBackground.addRoundedRect( QRect( 0, 0, this->width(), this->height() ),
                                   8, 8 );
    painter.setRenderHint( QPainter::SmoothPixmapTransform, true );
    painter.fillPath( pathBackground, QBrush( QColor( 255, 255, 255 ) ) );
    return QWidget::paintEvent( event );
}

void MessageBox::closeEvent( QCloseEvent *event ) {
    if ( m_eventLoop != NULL ) {
        m_eventLoop->exit();
    }
    event->accept();
}

MessageBox::~MessageBox() {}
