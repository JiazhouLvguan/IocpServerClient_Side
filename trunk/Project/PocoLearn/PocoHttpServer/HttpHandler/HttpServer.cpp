#include "stdafx.h"
#include "HttpHandler/HttpServer.h"
#include "HttpRequestHandlerFactory.h"

using namespace Poco::Net;
static HTTPServer* sg_server = nullptr;

bool CHttpServer::start()
{
    static HTTPServer server(new RequestHandlerFactory, 80);
    server.start();
    return true;
}
