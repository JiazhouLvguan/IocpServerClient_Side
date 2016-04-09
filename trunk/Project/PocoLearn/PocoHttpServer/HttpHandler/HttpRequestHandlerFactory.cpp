#include "stdafx.h"
#include "HttpReceiveFileHandler.h"
#include "HttpRequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory()
{
}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
	return new ReceiveFileHandler;
}
