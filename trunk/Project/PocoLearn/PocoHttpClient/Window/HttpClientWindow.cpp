#include "stdafx.h"
#include "HttpClientWindow.h"



CHttpClientWindow::CHttpClientWindow(LPCTSTR pzsXmlPath) :CBaseWindow(pzsXmlPath)
{
	
}

CHttpClientWindow::~CHttpClientWindow()
{

}

void CHttpClientWindow::InitWindow()
{
	CenterWindow();
}



bool CHttpClientWindow::PostFile()
{
	m_bIsPostFile = true;

	CEditUI* editFilePath = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editFiePath"));
	editFilePath->SetText(m_wstFilePath.c_str());
	try
	{
		Poco::URI url("http://127.0.0.1:80/");


		Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, url.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);
		Poco::Net::HTMLForm form;
		form.setEncoding(Poco::Net::HTMLForm::ENCODING_MULTIPART);

		std::string strFilePath;
		Poco::UnicodeConverter::convert(m_wstFilePath, strFilePath);
		form.addPart("file", new Poco::Net::FilePartSource(strFilePath));
		form.prepareSubmit(request);

		Poco::Net::HTTPClientSession httpSession(url.getHost(), url.getPort());
		httpSession.setTimeout(Poco::Timespan(20, 0));
		form.write(httpSession.sendRequest(request));


		Poco::Net::HTTPResponse res;
		std::istream &is = httpSession.receiveResponse(res);
		std::string strResponseInfo;
	}
	catch (Poco::Net::NetException & ex)
	{
		m_wstFilePath.clear();
		std::wstring wstrException;
		Poco::UnicodeConverter::convert(ex.displayText(),wstrException);
		editFilePath->SetText(wstrException.c_str());
		OutputDebugStringA(ex.displayText().c_str());
		m_bIsPostFile = false;
		return false;
	}
	catch (const Poco::InvalidAccessException &ex)
	{
		m_wstFilePath.clear();
		editFilePath->SetText(L"解析Json错误");
		m_bIsPostFile = false;
		OutputDebugStringA(ex.displayText().c_str());
		return false;
	}
	catch (const Poco::TimeoutException &ex)
	{
		m_wstFilePath.clear();
		editFilePath->SetText(L"超时");
		OutputDebugStringA(ex.displayText().c_str());
		m_bIsPostFile = false;
		return false;
	}
	m_wstFilePath.clear();
	editFilePath->SetText(L"发送Success");
	m_bIsPostFile = false;
	return true;
}

void CHttpClientWindow::Notify(TNotifyUI& msg)
{
	CDuiString strCtrlName = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strCtrlName == _T("btnClose"))
		{
			Close(IDCLOSE);
		}
		else if (strCtrlName == _T("btnSend"))
		{
			if (m_wstFilePath.empty())
			{
				CEditUI* editFilePath = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editFiePath"));
				editFilePath->SetText(L"请重新拖入文件发送");
				return;
			}
			else if (m_bIsPostFile)
			{
				CEditUI* editFilePath = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editFiePath"));
				editFilePath->SetText(L"正在发送文件");
			}
			else
			{
				std::thread tPostFile(&CHttpClientWindow::PostFile, this);
				tPostFile.detach();
			}	
		}
	}
}

LRESULT CHttpClientWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_SYSCOMMAND)
	{
		switch (wParam)
		{
		case SC_CLOSE:
		{
			Close();
			return 0;
		}
		default:
			break;
		}
	}
	if (WM_NCLBUTTONDBLCLK != uMsg)
	{
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	}
	return 0;
}

UILIB_RESOURCETYPE	CHttpClientWindow::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

LPCTSTR	 CHttpClientWindow::GetResourceID()	const
{
	return MAKEINTRESOURCE(IDR_UICONFIGURATION1);
}


LRESULT CHttpClientWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (uMsg == WM_DROPFILES)
	{
		
		WCHAR lpwszApk[256] = { 0 };
		DragQueryFile((HDROP)wParam, 0, lpwszApk, 256);

		m_wstFilePath = lpwszApk;
		CEditUI* editFilePath = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editFiePath"));
		editFilePath->SetText(m_wstFilePath.c_str());
		DragFinish((HDROP)wParam);
		bHandled = true;
		
	}

	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			bHandled = true;
			break;
		case VK_SPACE:
			bHandled = true;
			break;
		case SC_CLOSE:
			bHandled = true;
			break;
		default:
			break;
		}
	}
	
	return false;
}

