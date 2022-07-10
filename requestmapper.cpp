#include "requestmapper.h"
#include "global.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

RequestMapper::RequestMapper( QObject *parent )
    : HttpRequestHandler( parent ) {
    // empty
}

void RequestMapper::service( HttpRequest &request, HttpResponse &response ) {
    QByteArray path = request.getPath();
    qDebug( "RequestMapper: path=%s", path.data() );

    if ( path.startsWith( "/api" ) ) {
        response.setHeader( "Content-Type", "application/json" );
        // 获取版本号接口
        if ( path == "/api/version" ) {
            QJsonObject jsonObject;
            jsonObject.insert( "code", 200 );
            jsonObject.insert( "version", "0.0.1" );
            QJsonDocument jsonDocument( jsonObject );
            QByteArray    json = jsonDocument.toJson();
            response.write( json, true );
        } else {
            QJsonObject jsonObject;
            jsonObject.insert( "code", 404 );
            jsonObject.insert( "message", QStringLiteral( "接口地址不存在" ) );
            QJsonDocument jsonDocument( jsonObject );
            QByteArray    json = jsonDocument.toJson();
            response.write( json, true );
        }

    } else {
        staticFileController->service( request, response );
    }

    qDebug( "RequestMapper: finished request" );
    logger->clear( true, true );
}
