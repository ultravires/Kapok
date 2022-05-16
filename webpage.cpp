#include "webpage.h"

#include <QWebEngineCertificateError>

WebPage::WebPage( QObject *parent )
    : QWebEnginePage( parent ) {}

WebPage::WebPage( QWebEngineProfile *profile, QObject *parent )
    : QWebEnginePage( profile, parent ) {}

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
