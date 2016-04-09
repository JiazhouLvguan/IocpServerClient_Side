#include "stdafx.h"
#include "TimingCloseTranslucenceWindow.h"



CTimingCloseTranslucenceWindow::CTimingCloseTranslucenceWindow(LPCTSTR pzsXmlPath,int nTimerId):
CBaseWindow(pzsXmlPath)
{
	m_nTimerId = nTimerId;
	m_nTotal = 220;
}

LPCTSTR CTimingCloseTranslucenceWindow::GetWindowClassName() const
{
	return L"MessageBoxWindow";
}

void CTimingCloseTranslucenceWindow::InitWindow()
{
	m_pTimerControl = m_PaintManager.FindControl(L"timerControl");
}

void CTimingCloseTranslucenceWindow::Notify(TNotifyUI& msg)
{
	CDuiString strCtrlName = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strCtrlName == L"btnClose")
		{
			Close(WM_CLOSE);
		}
	}
	else if (msg.sType == L"timer")
	{
		TransparencyRun();
	}
}



LRESULT CTimingCloseTranslucenceWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCLBUTTONDBLCLK != uMsg)
	{
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	}
	return 0;
}




LRESULT CTimingCloseTranslucenceWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
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

void CTimingCloseTranslucenceWindow::OnFinalMessage(HWND /*hWnd*/)
{

}

CTimingCloseTranslucenceWindow::~CTimingCloseTranslucenceWindow()
{

}


void CTimingCloseTranslucenceWindow::SetShowInfo(std::wstring wstrShowInfo)
{
	m_PaintManager.KillTimer(m_pTimerControl);
	m_nTotal = 220;
	ShowWindow(true);
	CLabelUI* pLayoutShowInfo = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"LabShowInfo"));

	pLayoutShowInfo->SetText(wstrShowInfo.c_str());
	m_PaintManager.SetTimer(m_pTimerControl, m_nTimerId, 70);
}

void CTimingCloseTranslucenceWindow::TransparencyRun()
{
	m_nTotal-= 4;
	
	if (m_nTotal == 4)
	{
		m_nTotal = 220;
		m_PaintManager.KillTimer(m_pTimerControl);
		ShowWindow(false);
		return;
	}

	//m_PaintManager.SetTransparent(m_nTotal);
}
