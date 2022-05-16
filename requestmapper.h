#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT;
public:
    RequestMapper(QObject *parent = nullptr);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // REQUESTMAPPER_H
