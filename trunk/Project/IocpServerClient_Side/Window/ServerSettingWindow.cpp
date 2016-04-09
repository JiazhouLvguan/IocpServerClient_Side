#include "stdafx.h"
#include "ServerSettingWindow.h"


CServerSettingWindow::CServerSettingWindow(LPCTSTR pzsXmlPath) :CBaseWindow(pzsXmlPath)
{

}

CServerSettingWindow::~CServerSettingWindow()
{

}

LPCTSTR	 CServerSettingWindow::GetWindowClassName() const
{
	return L"ServerSettingWindow";
}


CControlUI*	 CServerSettingWindow::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}


void CServerSettingWindow::InitWindow()
{
	m_pEditPort = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editPort"));
	CenterWindow();
}



void CServerSettingWindow::Notify(TNotifyUI& msg)
{
	CDuiString strCtrlName = msg.pSender->GetName();
	if (msg.sType == L"click")
	{
		if (strCtrlName == L"btnClose")
			CloseWindow();
		else if (strCtrlName == L"btnSure")
		{
			std::wstring wstrnPort = m_pEditPort->GetText().GetData();
			if (wstrnPort.empty())
			{
				WarnWindow(L"请填入端口号");
				return;
			}
			
			std::string strnPort = nsAppCommon::ws2s(wstrnPort);
			int nPort = std::stoi(strnPort);
			if (nPort < 1023)
			{
				WarnWindow(L"请保持端口号大于1023");
				return;
			}
			
			{	
				InitServer();
				ShowWindow(false);
				HWND hServerWnd = ::FindWindow(TO_FIND_MAINWINDOW_DEFINED_CLASSNAME, TO_FIND_MAINWINDOW_DEFINED_NAME);
				::PostMessage(hServerWnd, WM_CLOSE_SERVERWINDOW, NULL, NULL);
			}
		}
	}
}

LRESULT CServerSettingWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_SYSCOMMAND)
	{
		switch (wParam)
		{
		case SC_CLOSE:
		{
			CloseWindow();
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

LRESULT	 CServerSettingWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return NULL;
}

UILIB_RESOURCETYPE	CServerSettingWindow::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

LPCTSTR	 CServerSettingWindow::GetResourceID()	const
{
	return MAKEINTRESOURCE(IDR_UICONFIGURATION1);
}

LRESULT CServerSettingWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
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

void CServerSettingWindow::InitSqlite()
{
	m_pCppSqlite = std::make_shared<CppSQLite3DB>();
	std::string strDbPath = nsAppCommon::ws2s(nsAppCommon::GetCurrentMoulde()) + "Server.db";
	m_pCppSqlite->open(strDbPath.c_str());

}

bool CServerSettingWindow::InitServer()
{
	bool bInitResult = true;
	try
	{
		InitSqlite();

		//从sqlite中取值 初始化服务器
		m_pIocpServer = std::make_shared<nsIocpServerClientNet::CIocpServer>("127.0.0.1", 1333);
	}
	catch (CppSQLite3Exception&)
	{
		//
		bInitResult = false;
	}
	catch (std::exception&)
	{
		bInitResult = false;
	}

	return bInitResult;

}

void CServerSettingWindow::WarnWindow(std::wstring wstrInfo)
{
	ShowMessageWindow(L"ModalWindow\\MessageBoxWindowClose.xml", wstrInfo);
}

void CServerSettingWindow::CloseWindow()
{
	if (IDOK == ShowMessageWindow(L"ModalWindow\\MessageBoxWindow.xml",L"即将退出服务器"))
	{
		HWND hServerWnd = ::FindWindow(TO_FIND_MAINWINDOW_DEFINED_CLASSNAME, TO_FIND_MAINWINDOW_DEFINED_NAME);
		::PostMessage(hServerWnd, WM_CLOSE_SERVERWINDOW, NULL,NULL);
	}
}

UINT CServerSettingWindow::ShowMessageWindow(std::wstring wstrXmlPath,std::wstring wstrInfo)
{
	CMessageWindow messageWindow(wstrXmlPath.c_str());
	messageWindow.Create(m_hWnd, NULL, UI_WNDSTYLE_DIALOG&~WS_VISIBLE, WS_EX_WINDOWEDGE);
	messageWindow.SetMessageTheme(wstrInfo.c_str());
	return	messageWindow.ShowModal();
}