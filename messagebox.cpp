#include "messagebox.h"
#include <QButtonGroup>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QRect>
#include <QSpacerItem>
#include <QVBoxLayout>

int MessageBox::showMessageBox( QWidget *parent, const QString &title,
                                const QString &text, MessageBoxType type,
                                MessageBoxButton buttons, bool isModal ) {
    MessageBox *messageBox = new MessageBox( parent );

    QLabel *titleLabel = new QLabel( title );
    titleLabel->setFont( QFont( "AlibabaPuHuiTi-Medium" ) );
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget( titleLabel );

    QLabel *textLabel = new QLabel( text );
    textLabel->setFont( QFont( "AlibabaPuHuiTi-Regular" ) );
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addWidget( textLabel );

    QPushButton *cancelButton = new QPushButton( QStringLiteral( "取消" ) );
    cancelButton->setVisible( true );
    cancelButton->setFixedSize( 64, 32 );
    cancelButton->setStyleSheet(
        "background-color: #DBDCDE; border-radius: 4px; color: #fff" );
    connect( cancelButton, SIGNAL( clicked() ), messageBox,
             SLOT( onCancelButtonClicked() ) );
    QPushButton *confirmButton = new QPushButton( QStringLiteral( "确认" ) );
    confirmButton->setVisible( false );
    confirmButton->setFixedSize( 64, 32 );
    confirmButton->setStyleSheet(
        "background-color: #3180F6; border-radius: 4px; color: #fff" );
    connect( confirmButton, SIGNAL( clicked() ), messageBox,
             SLOT( onConfirmButtonClicked() ) );

    switch ( buttons ) {
    case MessageBoxButton::ButtonConfirm:
        confirmButton->setVisible( true );
        break;
    case MessageBoxButton::ButtonCancel:
        cancelButton->setVisible( true );
        break;
    default:
        break;
    }

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(
        new QSpacerItem( 0, 0, QSizePolicy::Expanding ) );
    buttonLayout->addWidget( cancelButton );
    buttonLayout->addWidget( confirmButton );

    QVBoxLayout *mainLayout = new QVBoxLayout( messageBox );
    mainLayout->setContentsMargins( 24, 20, 24, 20 );
    mainLayout->addLayout( titleLayout );
    mainLayout->addLayout( contentLayout );
    mainLayout->addLayout( buttonLayout );
    if ( isModal ) {
        messageBox->setWindowModality( Qt::WindowModal );
        messageBox->exec();
        return messageBox->m_chooseResult;
    } else {
        messageBox->show();
    }
    return 0;
}

MessageBox::MessageBox( QWidget *parent )
    : QDialog( parent ) {
    setWindowFlags( Qt::Dialog | Qt::FramelessWindowHint );
    setAttribute( Qt::WA_QuitOnClose, true );
    setMinimumSize( 360, 160 );
    //    resize( 360, 160 );
}

void MessageBox::onCancelButtonClicked() {
    this->m_chooseResult = MessageBoxButton::ButtonCancel;
    this->close();
}

void MessageBox::onConfirmButtonClicked() {
    this->m_chooseResult = MessageBoxButton::ButtonConfirm;
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
