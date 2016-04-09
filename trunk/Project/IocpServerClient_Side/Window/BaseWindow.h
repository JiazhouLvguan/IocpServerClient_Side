#ifndef		__UIBASE_H_ZHOUFAN_10_10__
#define		__UIBASE_H_ZHOUFAN_10_10__


class CBaseWindow : public WindowImplBase
{
public:
	explicit CBaseWindow(LPCTSTR pszXmlPath) :m_strXmlPath(pszXmlPath)
	{}

	virtual LPCTSTR GetWindowClassName() const
	{
		return L"";
	}

	virtual CDuiString GetSkinFile()
	{
		return m_strXmlPath;
	}

	virtual CDuiString GetSkinFolder()
	{
		return _T("");
	}

protected:
	CDuiString m_strXmlPath;
};




#endif