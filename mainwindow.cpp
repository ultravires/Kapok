#include "mainwindow.h"
#include "jsbridge.h"
#include "ui_mainwindow.h"
#include "webpage.h"
#include "webview.h"
#include "widget.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent ) {
    QFileInfo jsFileInfo( QDir::currentPath() + "/qwebchannel.js" );

    if ( !jsFileInfo.exists() ) {
        QFile::copy( ":/qtwebchannel/qwebchannel.js",
                     jsFileInfo.absoluteFilePath() );
    }

    setWindowFlags( Qt::FramelessWindowHint | windowFlags() );
    setAttribute( Qt::WA_QuitOnClose, true );
    setAttribute( Qt::WA_TranslucentBackground, true );
    setStyleSheet( "background-color:transparent" );
    setAutoFillBackground( false );

    QUrl defaultURL = QUrl( "http://127.0.0.1:10086/#/login" );

    Widget *widget = new Widget();
    widget->resize( this->width(), this->height() );
    widget->webview->load( defaultURL );

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( widget, 0, 0 );

    resize( 900, 600 );
    QWidget *centralWidget = new QWidget();
    setCentralWidget( centralWidget );
    centralWidget->setLayout( mainLayout );
}

MainWindow::~MainWindow() {}
