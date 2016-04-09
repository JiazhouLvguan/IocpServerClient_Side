#include "stdafx.h"
#include "ServerWindow.h"


CServerWindow::CServerWindow(LPCTSTR pzsXmlPath) :CBaseWindow(pzsXmlPath)
{

}

CServerWindow::~CServerWindow()
{

}

LPCTSTR	 CServerWindow::GetWindowClassName() const
{
	return TO_FIND_MAINWINDOW_DEFINED_CLASSNAME;
}


void CServerWindow::OnFinalMessage(HWND /*hWnd*/)
{

}

CControlUI*	 CServerWindow::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void CServerWindow::InitWindow()
{
	m_pServerSettingWindow = std::make_shared<CServerSettingWindow>(L"ServerSettingSkin\\ServerSettingWindow.xml");

	m_pServerSettingWindow->Create(NULL, L"ServerSettingWindow", UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	
	CenterWindow();
}



void CServerWindow::Notify(TNotifyUI& msg)
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

LRESULT CServerWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_SYSCOMMAND)
	{
		switch (wParam)
		{
		case SC_CLOSE:
		{
			m_pServerSettingWindow->CloseWindow();
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

LRESULT	 CServerWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_CLOSE_SERVERWINDOW)
	{
		Close(IDCLOSE);
		bHandled = TRUE;
	}


	return NULL;
}



UILIB_RESOURCETYPE	CServerWindow::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

LPCTSTR	 CServerWindow::GetResourceID()	const
{
	return MAKEINTRESOURCE(IDR_UICONFIGURATION1);
}




LRESULT CServerWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
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

