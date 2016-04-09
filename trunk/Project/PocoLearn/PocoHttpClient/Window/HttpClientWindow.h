#ifndef		__HTTPSERVER_WINDOW_H__
#define		__HTTPSERVER_WINDOW_H__

#include "BaseWindow.h"

#include "../resource.h"

class CHttpClientWindow :public CBaseWindow
{
private:
	bool		m_bIsPostFile = false;

private:
	std::wstring m_wstFilePath;

public:
	CHttpClientWindow(LPCTSTR pzsXmlPath);
	~CHttpClientWindow();

	void			InitWindow();


	void			Notify(TNotifyUI& msg);

	LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	UILIB_RESOURCETYPE	GetResourceType() const;

	LPCTSTR				GetResourceID() const;

	bool				PostFile();

};




#endif