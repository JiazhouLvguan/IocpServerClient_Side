#include "stdafx.h"

#include "Window/ServerWindow.h"


#include <set>

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	HWND hOldWnd = ::FindWindow(TO_FIND_MAINWINDOW_DEFINED_CLASSNAME, TO_FIND_MAINWINDOW_DEFINED_NAME);
	if (hOldWnd)
	{
		::ShowWindow(hOldWnd, SW_SHOWNORMAL);
		::SetForegroundWindow(hOldWnd);
	}
	else
	{
		::CoInitialize(NULL);
		CPaintManagerUI::SetInstance(hInstance);

		DWORD dwStyle = UI_WNDSTYLE_FRAME&&~WS_VISIBLE;

		CServerWindow serverWindow(L"IocpServerClient_SideWindow.xml");

		serverWindow.Create(NULL, TO_FIND_MAINWINDOW_DEFINED_NAME, dwStyle, WS_EX_WINDOWEDGE);
		serverWindow.ShowModal(false);
		::CoUninitialize();
	}

	return 0;
}

