#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <httprequesthandler.h>

using namespace stefanfrings;

class RequestHandler: public HttpRequestHandler
{
public:
    RequestHandler(QObject* parent = nullptr);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // REQUESTHANDLER_H
