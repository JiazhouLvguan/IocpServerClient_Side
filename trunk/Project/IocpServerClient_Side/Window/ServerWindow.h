#ifndef		__SERVER_WINDOW_ZHOUFAN_2_15_H__
#define		__SERVER_WINDOW_ZHOUFAN_2_15_H__


#include "resource.h"
#include "BaseWindow.h"
#include "ServerSettingWindow.h"


class CServerWindow :public CBaseWindow
{
private:
	std::shared_ptr<CServerSettingWindow>	m_pServerSettingWindow;

public:
	CServerWindow(LPCTSTR);
	
	LPCTSTR			GetWindowClassName() const;

	void			InitWindow();

	void			OnFinalMessage(HWND /*hWnd*/);

	CControlUI*		CreateControl(LPCTSTR pstrClass);

	void			Notify(TNotifyUI& msg);

	LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT			HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	UILIB_RESOURCETYPE	GetResourceType() const;

	LPCTSTR				GetResourceID() const;

	~CServerWindow();
};

#endif