#ifndef _REQUESTHANDLERFACTORY_H
#define _REQUESTHANDLERFACTORY_H



class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    RequestHandlerFactory();

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest &request) override final;
	
};

#endif // REQUESTHANDLERFACTORY_H
