#ifndef _APPCOMMON_2016_4_1_H_
#define _APPCOMMON_2016_4_1_H_


#define MAX_PATH          260

#include <stdio.h>
#include <cstdlib>
#include <tchar.h>
#include <string>


#include <string> 
#include <comutil.h>  

#pragma comment(lib, "comsuppw.lib")   


namespace nsAppCommon
{
	inline std::string ws2s(const std::wstring& ws)
	{
		_bstr_t t = ws.c_str();
		char* pchar = (char*)t;
		std::string result = pchar;
		return result;
	}

	inline std::wstring s2ws(const std::string& s)
	{
		_bstr_t t = s.c_str();
		wchar_t* pwchar = (wchar_t*)t;
		std::wstring result = pwchar;
		return result;
	}

	inline std::wstring GetCurrentMoulde()
	{
		TCHAR fullName[MAX_PATH] = { 0 };
		GetModuleFileNameW(NULL, fullName, MAX_PATH);

		std::wstring  wstrPath = fullName;

		std::wstring::size_type pos = wstrPath.find_last_of(L"\\");
		if (pos != std::wstring::npos)
		{
			wstrPath = wstrPath.substr(0, pos + 1);
		}
		return wstrPath;
	}
}

#endif