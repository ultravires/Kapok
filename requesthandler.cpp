#include <requesthandler.h>

RequestHandler::RequestHandler(QObject* parent): HttpRequestHandler(parent)
{
    // TODO
}

void RequestHandler::service(HttpRequest& request, HttpResponse& response)
{
    // TODO
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    response.write("<html><body>");
    response.write("Hallo ");
    response.write("</body></html>");
}
