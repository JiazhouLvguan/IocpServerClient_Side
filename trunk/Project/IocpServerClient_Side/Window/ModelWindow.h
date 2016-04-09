#ifndef		__MODALWINDOW_2016_4_1_H__
#define		__MODALWINDOW_2016_4_1_H__

#include "BaseWindow.h"

/*
	调用 方式

	CModelWindow modelWindow(L"...xml", L"Info...");
	
	modelWindow.Create(m_hWnd, _T("modelMessage"), UI_WNDSTYLE_DIALOG&~WS_VISIBLE, WS_EX_WINDOWEDGE);


	std::thread ThreadRun(&CLASSNAME::CLASSFUNCTION, this,para..., modelWindow.GetHWND());
	threadGetApkInfoAndSetApkInfo.detach();	//线程退出  时 postmessage 给 modelwindow 结束 showmodal
	
	modelWindow.ShowModal();

*/


class CModelWindow:public CBaseWindow
{
	private:
		std::wstring	m_wstrLabelInfo;
		CLabelUI*		m_pLabelInfo;
	public:
		CModelWindow(LPCTSTR,std::wstring wstrLabInfo);

		LPCTSTR			GetWindowClassName() const;

		void			InitWindow();

		void			OnFinalMessage(HWND /*hWnd*/);

		void			Notify(TNotifyUI& msg);

		LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

		~CModelWindow();	
};




#endif