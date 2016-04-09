#include "stdafx.h"
#include "ModelWindow.h"



CModelWindow::CModelWindow(LPCTSTR pzsXmlPath,std::wstring wstrLabelInfo) :
CBaseWindow(pzsXmlPath)
{
	m_wstrLabelInfo = wstrLabelInfo;
}

LPCTSTR CModelWindow::GetWindowClassName() const
{
	return L"ModelWindow";
}

void CModelWindow::InitWindow()
{

	m_pLabelInfo = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labInfo"));

	m_pLabelInfo->SetText(m_wstrLabelInfo.c_str());

	CenterWindow();
}

void CModelWindow::Notify(TNotifyUI& msg)
{
	
}

LRESULT CModelWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCLBUTTONDBLCLK != uMsg)
	{
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	}
	return 0;
}




LRESULT CModelWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
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

void CModelWindow::OnFinalMessage(HWND /*hWnd*/)
{

}

CModelWindow::~CModelWindow()
{

}



