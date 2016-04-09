#pragma once


#include "BaseWindow.h"


/*
	调用方式
	1.创建窗体 窗体类型 PopWindow，因为子窗体不支持 半透明
	CTimingCloseTranslucenceWindow* ptimingCloseTranslucenceWindow = new CTimingCloseTranslucenceWindow(L"....xml", TIMEID);
	ptimingCloseTranslucenceWindow->Create(m_hWnd, _T("TimingCloseTranslucenceWindow"), UI_WNDSTYLE_DIALOG&~WS_VISIBLE, NULL);

	2.因为是 PopWindow,所以  移动此窗体依赖的窗体时，需要给此窗体发送消息 让其移动 
		在DUI消息流中截获消息
		if (uMsg == WM_MOVE)
		{
			if (ptimingCloseTranslucenceWindow)
				ptimingCloseTranslucenceWindow->设置位置; 此接口需要实现
		}

	3.ptimingCloseTranslucenceWindow->SetShowInfo(L"...");
*/

class CTimingCloseTranslucenceWindow:public CBaseWindow
{
private:
	int m_nTotal;

	int m_nTimerId;

	CControlUI*	m_pTimerControl;

	public:
		CTimingCloseTranslucenceWindow(LPCTSTR pzsXmlPath,int nTimerId);

		LPCTSTR			GetWindowClassName() const;

		void			InitWindow();

		void			OnFinalMessage(HWND /*hWnd*/);

		void			Notify(TNotifyUI& msg);

		LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

		void			SetShowInfo(std::wstring wstrShowInfo);

		void			TransparencyRun();

		~CTimingCloseTranslucenceWindow();	
};
