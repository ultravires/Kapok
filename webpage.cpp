#include "webpage.h"

#include <QMessageBox>
#include <QWebEngineCertificateError>

WebPage::WebPage( QObject *parent )
    : QWebEnginePage( parent ) {}

WebPage::WebPage( QWebEngineProfile *profile, QObject *parent )
    : QWebEnginePage( profile, parent ) {
    connect( this, &QWebEnginePage::featurePermissionRequested, this,
             &WebPage::handleFeaturePermissionRequested );
}

inline QString questionForFeature( QWebEnginePage::Feature feature ) {
//    switch ( feature ) {
//    case QWebEnginePage::Geolocation:
//        return QString::fromLocal8Bit( "允许 %1 访问您的位置信息？" );
//    case QWebEnginePage::MediaAudioCapture:
//        return QString::fromLocal8Bit( "允许 %1 访问您的摄像头?" );
//    case QWebEnginePage::MediaVideoCapture:
//        return QString::fromLocal8Bit( "允许 %1 访问您的摄像头？" );
//    case QWebEnginePage::MediaAudioVideoCapture:
//        return QString::fromLocal8Bit( "允许 %1 访问您的麦克风和摄像头？" );
//    case QWebEnginePage::MouseLock:
//        return QString::fromLocal8Bit( "允许 %1 锁住鼠标？" );
//    case QWebEnginePage::DesktopVideoCapture:
//        return QString::fromLocal8Bit( "允许 %1 录取桌面画面？" );
//    case QWebEnginePage::DesktopAudioVideoCapture:
//        return QString::fromLocal8Bit( "允许 %1 录取桌面画面和声音？" );
//    case QWebEnginePage::Notifications:
//        return QString::fromLocal8Bit( "允许 %1 显示通知？" );
//    default:
//        return QString::fromLocal8Bit( "" );
//    }
}

void WebPage::handleFeaturePermissionRequested(
    const QUrl &securityOrigin, QWebEnginePage::Feature feature ) {
    setFeaturePermission( securityOrigin, feature, PermissionGrantedByUser );

    //    QString title = QString::fromLocal8Bit( "权限申请" );
    //    QString question =
    //        questionForFeature( feature ).arg( securityOrigin.host() );
    //    if ( !question.isEmpty() &&
    //         QMessageBox::question( view()->window(), title, question ) ==
    //             QMessageBox::Yes ) {
    //        setFeaturePermission( securityOrigin, feature,
    //                              PermissionGrantedByUser );
    //    } else {
    //        setFeaturePermission( securityOrigin, feature,
    //        PermissionDeniedByUser );
    //    }
}

// https://doc.qt.io/qt-5/qwebenginepage.html#certificateError
bool WebPage::certificateError( const QWebEngineCertificateError &error ) {
#if QT_VERSION >= QT_VERSION_CHECK( 5, 4, 0 ) &&                               \
    QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    qDebug( "%s %s %s", qPrintable( error.url().toString() ),
            qPrintable( tr( "Certificate Error" ) ),
            qPrintable( error.errorDescription() ) );
#else
    qDebug( "%s %s %s", qPrintable( error.url().toString() ),
            qPrintable( tr( "Certificate Error" ) ),
            qPrintable( error.description() ) );
#endif
    return true;
}
