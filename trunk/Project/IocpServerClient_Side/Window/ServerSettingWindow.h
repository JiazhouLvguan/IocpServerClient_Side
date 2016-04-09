#ifndef		__SERVERSETTING_WINDOW_ZHOUFAN_2_15_H__
#define		__SERVERSETTING_WINDOW_ZHOUFAN_2_15_H__

#include "resource.h"
#include "BaseWindow.h"
#include "MessageWindow.h"


class CServerSettingWindow :public CBaseWindow
{
	friend class CServerWindow;

private:
	std::shared_ptr<CppSQLite3DB>							m_pCppSqlite;
	std::shared_ptr<nsIocpServerClientNet::CIocpServer>		m_pIocpServer;
	
	CEditUI*												m_pEditPort;

public:
	CServerSettingWindow(LPCTSTR);

	LPCTSTR			GetWindowClassName() const;

	void			InitWindow();

	CControlUI*		CreateControl(LPCTSTR pstrClass);

	void			Notify(TNotifyUI& msg);

	LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT			HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	UILIB_RESOURCETYPE	GetResourceType() const;

	LPCTSTR				GetResourceID() const;

	~CServerSettingWindow();

	void			InitSqlite();

	bool			InitServer();
	

	void			WarnWindow(std::wstring wstrInfo);
	void			CloseWindow();

	UINT			ShowMessageWindow(std::wstring wstrXmlPath,std::wstring wstrInfo);


};

#endif