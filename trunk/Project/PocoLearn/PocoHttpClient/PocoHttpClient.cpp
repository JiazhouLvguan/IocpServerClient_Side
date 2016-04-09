// PocoHttpClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Window/HttpClientWindow.h"


#define		TO_FIND_HTTPCLIENT_MAINWINDOW_DEFINED_CLASSNAME		L"FILE_HTTPCLIENT_HANDLER_WINDOW_CLASSNAME"
#define		TO_FIND_HTTPCLIENT_MAINWINDOW_DEFINED_NAME			L"FILE_HTTPCLIENT_HANDLER_NAME_ZHOU_FAN_2016_3_11"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	HWND hOldWnd = ::FindWindow(TO_FIND_HTTPCLIENT_MAINWINDOW_DEFINED_CLASSNAME, TO_FIND_HTTPCLIENT_MAINWINDOW_DEFINED_NAME);
	if (hOldWnd)
	{
		::ShowWindow(hOldWnd, SW_SHOWNORMAL);
		::SetForegroundWindow(hOldWnd);
	}
	else
	{
		::CoInitialize(NULL);
		CPaintManagerUI::SetInstance(hInstance);


		DWORD dwStyle = UI_WNDSTYLE_FRAME&~WS_THICKFRAME;

		CHttpClientWindow httpClientWindow(L"HttpClient.xml");
		
		httpClientWindow.Create(NULL, NULL, dwStyle, WS_EX_WINDOWEDGE | WS_EX_TOPMOST | WS_EX_ACCEPTFILES);

		httpClientWindow.ShowModalByOldAttribute();
		::CoUninitialize();
	}
	
	return 0;
}

