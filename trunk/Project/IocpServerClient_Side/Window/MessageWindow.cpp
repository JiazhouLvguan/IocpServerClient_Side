#include "stdafx.h"
#include "MessageWindow.h"



CMessageWindow::CMessageWindow(LPCTSTR pzsXmlPath) :
m_pLabShowInfo(NULL),
CBaseWindow(pzsXmlPath)
{

}

LPCTSTR CMessageWindow::GetWindowClassName() const
{
	return L"QtMainWindowMessageBoxWindow";
}

void CMessageWindow::InitWindow()
{
	m_pLabShowInfo = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labShowInfo"));

	CenterWindow();
}

void CMessageWindow::Notify(TNotifyUI& msg)
{
	CDuiString strCtrlName = msg.pSender->GetName();

	if (msg.sType == L"click")
	{
		if (strCtrlName == L"btnClose"){
			Close(IDCANCEL); return;}
		if (msg.pSender->GetName() == _T("btnYes")) {
			Close(IDOK);return;}
		else if (msg.pSender->GetName() == _T("btnNo")) {
			Close(IDCANCEL);return;}
	}
}

LRESULT CMessageWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCLBUTTONDBLCLK != uMsg)
	{
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	}
	return 0;
}




LRESULT CMessageWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
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

void CMessageWindow::OnFinalMessage(HWND /*hWnd*/)
{

}

CMessageWindow::~CMessageWindow()
{
	
}

void CMessageWindow::SetMessageTheme(LPCWSTR	lpwstrTheme)
{
	m_pLabShowInfo->SetText(lpwstrTheme);
}

