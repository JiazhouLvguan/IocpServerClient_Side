#include "stdafx.h"
#include "HttpServerWindow.h"



CHttpServerWindow::CHttpServerWindow(LPCTSTR pzsXmlPath) :CBaseWindow(pzsXmlPath)
{
	
}

CHttpServerWindow::~CHttpServerWindow()
{

}

void CHttpServerWindow::InitWindow()
{
	CenterWindow();
}





void CHttpServerWindow::Notify(TNotifyUI& msg)
{
	CDuiString strCtrlName = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strCtrlName == _T("btnClose"))
		{
			Close(IDCLOSE);
		}
		
	}
}

LRESULT CHttpServerWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_SYSCOMMAND)
	{
		switch (wParam)
		{
		case SC_CLOSE:
		{
			PostQuitMessage(0);
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

UILIB_RESOURCETYPE	CHttpServerWindow::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

LPCTSTR	 CHttpServerWindow::GetResourceID()	const
{
	return MAKEINTRESOURCE(IDR_UICONFIGURATION1);
}


LRESULT CHttpServerWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (uMsg == WM_DROPFILES)
	{
		
		WCHAR lpwszApk[256] = { 0 };
		DragQueryFile((HDROP)wParam, 0, lpwszApk, 256);

		
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

