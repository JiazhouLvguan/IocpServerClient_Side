#ifndef		__HTTPSERVER_WINDOW_H__
#define		__HTTPSERVER_WINDOW_H__

#include "BaseWindow.h"

#include "../resource.h"

class CHttpServerWindow :public CBaseWindow
{

private:
	

public:
	CHttpServerWindow(LPCTSTR pzsXmlPath);
	~CHttpServerWindow();

	void			InitWindow();


	void			Notify(TNotifyUI& msg);

	LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	UILIB_RESOURCETYPE	GetResourceType() const;

	LPCTSTR				GetResourceID() const;


};




#endif