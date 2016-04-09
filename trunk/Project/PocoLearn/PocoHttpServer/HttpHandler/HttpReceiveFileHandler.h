#ifndef _HTTP_RECEIVE_FILE_HANDLER_H_
#define _HTTP_RECEIVE_FILE_HANDLER_H_



class ReceiveFileHandler : public Poco::Net::HTTPRequestHandler
{
public:
	ReceiveFileHandler();

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override final;
};

#endif // ReceiveFileHandler_H
