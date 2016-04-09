#include "stdafx.h"
#include "FileHandler.h"
#include "HttpReceiveFileHandler.h"


using namespace Poco::Net;

ReceiveFileHandler::ReceiveFileHandler()
{
}

void ReceiveFileHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::JSON::Object js;

	try
	{
		CFileHandler apkPartHandler;
		HTMLForm form(request, request.stream(), apkPartHandler);
		if (apkPartHandler.isReady())
		{
			Poco::File tempApkFile(apkPartHandler.getFileName());
			tempApkFile.moveTo("D:\\text.file");
		}
		else
		{
			js.set("result", false);
			js.set("msg", "apkÎÄ¼þ±£´æÊ§°Ü");
		}
	}
	catch (const Poco::Exception& e)
	{
		js.clear();
		js.set("result", false);
		js.set("msg", e.displayText());
	}

	response.setStatus(HTTPResponse::HTTP_OK);
	response.setContentType("text/json;charset=utf-8");
	js.stringify(response.send(), 4);
}
