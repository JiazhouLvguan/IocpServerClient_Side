#include "stdafx.h"
#include "ExceptionWarpper.h"

namespace nsIocpServerClientUtility
{
	CExceptionBase::CExceptionBase(const char* str)
	{
		_msg = str;
	}
	CExceptionBase::CExceptionBase(std::string& str)
	{
		_msg = str;
	}
	CExceptionBase::CExceptionBase(std::string&, CExceptionBase&, int nErrorCode)
	{

	}
	CExceptionBase::CExceptionBase(CExceptionBase&)
	{

	}
	CExceptionBase::CExceptionBase(std::string&, std::string&, int nErrorCode)
	{

	}

	CExceptionBase::~CExceptionBase() throw()
	{

	}

	const char* CExceptionBase::name() const throw()
	{
		return "BaseException";
	}

	const char* CExceptionBase::className() const throw()
	{
		return typeid(*this).name();
	}

	const char* CExceptionBase::what() const throw()
	{
		return name();
	}
	
	//IOCP线程异常类
	MAKEEXCEPTIONCLASSIMPLEMENT(CExceptionSocket, CExceptionBase, "ExceptionSocket");
	MAKEEXCEPTIONCLASSIMPLEMENT(CExceptionInitNet, CExceptionBase, "ExceptionInitNet");
	MAKEEXCEPTIONCLASSIMPLEMENT(CExceptionThreadPool, CExceptionBase,"ExceptionThreadPool");
	
}


/*MAKEEXCEPTIONCLASSIMPLEMENT(CExceptionImplation, CExceptionBase, "ExceptionImplationImplation")*/