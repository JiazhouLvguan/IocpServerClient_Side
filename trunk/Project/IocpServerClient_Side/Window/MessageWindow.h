#ifndef		__MESSAGEWINDOW_2016_4_24_H__
#define		__MESSAGEWINDOW_2016_4_24_H__

#include "BaseWindow.h"


/*
	调用方式

	CMessageWindow messageWindow(L"....xml");
	messageWindow.Create(m_hWnd, NULL, UI_WNDSTYLE_DIALOG&~WS_VISIBLE, WS_EX_WINDOWEDGE);
	messageWindow.SetMessageTheme(wstrThemeInfo.c_str());
	messageWindow.ShowModal();

*/

class CMessageWindow:public CBaseWindow
{
	private:
		CLabelUI*		m_pLabShowInfo;
		
	public:
		CMessageWindow(LPCTSTR);

		LPCTSTR			GetWindowClassName() const;

		void			InitWindow();

		void			OnFinalMessage(HWND /*hWnd*/);


		void			Notify(TNotifyUI& msg);

		LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

		~CMessageWindow();

		void			SetMessageTheme(LPCWSTR	lpwstrTheme);
	
};


#endif