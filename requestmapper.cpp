#include "global.h"
#include "requestmapper.h"

RequestMapper::RequestMapper(QObject* parent)
    : HttpRequestHandler(parent)
{
    // empty
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path = request.getPath();
    qDebug("RequestMapper: path=%s", path.data());

    staticFileController->service(request, response);

    qDebug("RequestMapper: finished request");
    logger->clear(true,true);
}
