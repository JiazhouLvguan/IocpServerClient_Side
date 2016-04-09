#pragma once


#include "BaseWindow.h"


/*
	���÷�ʽ
	1.�������� �������� PopWindow����Ϊ�Ӵ��岻֧�� ��͸��
	CTimingCloseTranslucenceWindow* ptimingCloseTranslucenceWindow = new CTimingCloseTranslucenceWindow(L"....xml", TIMEID);
	ptimingCloseTranslucenceWindow->Create(m_hWnd, _T("TimingCloseTranslucenceWindow"), UI_WNDSTYLE_DIALOG&~WS_VISIBLE, NULL);

	2.��Ϊ�� PopWindow,����  �ƶ��˴��������Ĵ���ʱ����Ҫ���˴��巢����Ϣ �����ƶ� 
		��DUI��Ϣ���нػ���Ϣ
		if (uMsg == WM_MOVE)
		{
			if (ptimingCloseTranslucenceWindow)
				ptimingCloseTranslucenceWindow->����λ��; �˽ӿ���Ҫʵ��
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
