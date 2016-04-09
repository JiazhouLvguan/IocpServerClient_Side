#pragma once

#include <windows.h>
#include <stdexcept>
#include <string>

/*
	异常类的封装
	//只做了很简单的 封装  
*/

namespace nsIocpServerClientUtility
{
	class CExceptionBase :public std::exception
	{
	private:
		std::string				_msg;
		CExceptionBase*			_pNested;
		int						_code;
	public:
		CExceptionBase(const char*);
		CExceptionBase(std::string&);
		CExceptionBase(std::string&, CExceptionBase&, int nErrorCode = 0);
		CExceptionBase(CExceptionBase&);
		CExceptionBase(std::string&, std::string&, int nErrorCode = 0);

		~CExceptionBase() throw();

		virtual const char* name() const throw();
		virtual const char* className() const throw();
		virtual const char* what() const throw();
	};

	
#define EXPORTDEFINE 

#define  MAKEEXCEPTIONCLASSDECLARATION(EXPORTDEFINE,EXCEPTION,BASEEXCEPTION)	\
	class EXPORTDEFINE EXCEPTION:public BASEEXCEPTION				\
			{																\
		public:														\
			const char* name() const throw();							\
			const char* className() const throw();						\
			EXCEPTION(const char* pcz);									\
			EXCEPTION(std::string&);									\
			EXCEPTION(std::string&, CExceptionBase&, int nErrorCode = 0);	\
			EXCEPTION(CExceptionBase&);										\
			EXCEPTION(std::string&, std::string&, int nErrorCode = 0);			\
			};

#define MAKEEXCEPTIONCLASSIMPLEMENT(EXCEPTION,BASEEXCEPTION,NAME)\
		EXCEPTION::EXCEPTION(const char* pcz):BASEEXCEPTION(pcz)\
				{																																		\
																																				\
				}																																		\
		EXCEPTION::EXCEPTION(std::string& str):BASEEXCEPTION(str)\
				{																																		\
																																				\
				}																																		\
		EXCEPTION::EXCEPTION(std::string& str, CExceptionBase& exceptionParactice, int nErrorCode):BASEEXCEPTION(str,exceptionParactice,nErrorCode)	\
				{																																					\
																																							\
				}																																					\
		EXCEPTION::EXCEPTION(CExceptionBase& exceptionParactice):BASEEXCEPTION(exceptionParactice)												\
				{																																\
																																		\
				}																																\
		EXCEPTION::EXCEPTION(std::string& str, std::string& str2, int nErrorCode):BASEEXCEPTION(str,str2,nErrorCode)								\
				{																																\
																																		\
				}																																\
		const char* EXCEPTION::name() const throw()							\
				{																	\
			return NAME;													\
				}																	\
		const char* EXCEPTION::className() const throw()						\
				{																		\
				return typeid(*this).name();									\
				}																		


	MAKEEXCEPTIONCLASSDECLARATION(EXPORTDEFINE, CExceptionSocket, CExceptionBase);
	MAKEEXCEPTIONCLASSDECLARATION(EXPORTDEFINE, CExceptionInitNet, CExceptionBase);
	MAKEEXCEPTIONCLASSDECLARATION(EXPORTDEFINE, CExceptionThreadPool, CExceptionBase);
	
	
}





//MAKEEXCEPTIONCLASSIMPLEMENT(CExceptionImplation, CExceptionBase, "ExceptionImplationImplation")


