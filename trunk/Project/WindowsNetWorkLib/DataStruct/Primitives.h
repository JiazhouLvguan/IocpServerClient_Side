#ifndef __PRIMITIVES_H_
#define __PRIMITIVES_H_

#include <winsock2.h>

template<typename _TClass>
struct Delete_ElementPtr{
	void operator()(_TClass* pElem){ if(pElem) {delete pElem;} }
};

template <typename _Ty>
inline bool equal_t(_Ty val1, _Ty val2)
{
	return val1 == val2;
}

#define Delete_ElemArray(_ElemArray) \
	if(_ElemArray) {delete[] _ElemArray; _ElemArray = NULL;}

#define Delete_IFPtr(_ElemPtr) \
	if(_ElemPtr) {delete _ElemPtr; _ElemPtr = NULL;}

#define Delete_IFPtr_List(class, _ElemPtrList) \
	std::for_each(_ElemPtrList.begin(), _ElemPtrList.end(),  \
	Delete_ElementPtr<class>());  _ElemPtrList.clear();

#define Delete_IFPtr_ListEx(_ElemPtrList) \
	auto _iter = _ElemPtrList.begin(); \
	for(; _iter != _ElemPtrList.end(); ++_iter) { \
		Delete_IFPtr(*_iter); \
		} \
	_ElemPtrList.clear();

#define Delete_IFPtr_List_With_Func(_ElemPtrList, _DeleteFunc) \
	std::for_each(_ElemPtrList.begin(), _ElemPtrList.end(),  \
	_DeleteFunc); _ElemPtrList.clear();

#define Delete_IFWndPtr(_wndPtr) \
	if (_wndPtr) { \
		if (::IsWindow(_wndPtr->m_hWnd)){ \
			::DestroyWindow(_wndPtr->m_hWnd); \
				} \
		delete _wndPtr; \
		} \
	_wndPtr = NULL;

#define Delete_IFWndPtr_List(_ElemPtrList) \
	auto _iterEnd = _ElemPtrList.end(); \
	for (auto _iter = _ElemPtrList.begin(); _iter != _iterEnd; ++_iter) { \
		Delete_IFWndPtr((*_iter)); \
		} \
	_ElemPtrList.clear();

#define Check_ElemPtr_Available_With_Return(_ElemPtr, _RET) \
	if(NULL == _ElemPtr) return (_RET); 

#define Check_ElemPtr_Available(_ElemPtr) \
	if(NULL == _ElemPtr) return ; 

#define Check_IFIter_End(_iter, _end) \
	if (_iter == _end)  return ; 

#define  LOAD_WINSOCK2_FUNC(Socket, Guid_Func, lpFunc) \
{\
	DWORD dwBytes = 0;\
	if (SOCKET_ERROR == WSAIoctl(Socket, \
	SIO_GET_EXTENSION_FUNCTION_POINTER,\
	&Guid_Func,\
	sizeof(Guid_Func),\
	&lpFunc,\
	sizeof(lpFunc),\
	&dwBytes, \
	NULL,\
	NULL))\
	{\
	\
	}\
}\

// 名称字符串最大字符个数
#define Max_Name_Chars 128


#endif//__PRIMITIVES_H_