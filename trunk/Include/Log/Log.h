#ifndef EYEGLE_COMMON_CApplog_H
#define EYEGLE_COMMON_CApplog_H

#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#ifdef WIN32
#include <process.h>
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/unistd.h>
#endif
#include <Mutex/MutexWapper.h>
#include <iostream>

#define APP_LOG(LEVEL) itstation::common::CApplogFinisher() = itstation::common::CApplogInput(LEVEL, __FILE__, __LINE__)

namespace nsIocpServerClientUtility
{
	class CApplog
	{
	public:
		enum enumLevel{
			LOG_DEBUG_LIB = 1,
			LOG_INFO,
			LOG_DEBUG,
			LOG_WARNING,
			LOG_ERROR,
			LOG_CRITICAL
		};

		// standard interface for user
		static void SetLogLevel(unsigned int loglevel);
		std::string GetTimeStr();

		void Log(enumLevel elevel, const std::string& info, const std::string& msg);

		static CApplog* GetInstance();

		class DestructorClass //它的唯一工作就是在析构函数中删除CSingleton的实例 
		{
		public:
			~DestructorClass()
			{
				if (CApplog::instance_)
				{
					CCriticalMutexWapper lock(m_criticalMutex);
					if (CApplog::instance_)
					{
						delete CApplog::instance_;
						CApplog::instance_ = NULL;
					}
				}
			}
		};
		static DestructorClass dest;
	private:
		CApplog();
		virtual ~CApplog();

		static CApplog* instance_;

		static int log_level;

		static CCriticalMutex m_criticalMutex;
	};

	class CApplogInput
	{
	private:
		std::stringstream info;
		std::stringstream message_stream;
		CApplog::enumLevel m_elevel;
	public:
		CApplogInput(CApplog::enumLevel elevel, const char* filename, int line) :m_elevel(elevel)
		{
			info << filename << ":" << line;
		};

		friend class CApplogFinisher;
		CApplogInput& operator<<(char c)                 { message_stream << c; return *this; };
		CApplogInput& operator<<(short s)                { message_stream << s; return *this; };
		CApplogInput& operator<<(int n)                  { message_stream << n; return *this; };
		CApplogInput& operator<<(unsigned int un)        { message_stream << un; return *this; };
		CApplogInput& operator<<(float f)                { message_stream << f; return *this; };
		CApplogInput& operator<<(double d)               { message_stream << d; return *this; };
		CApplogInput& operator<<(long l)                 { message_stream << l; return *this; };
		CApplogInput& operator<<(const char* msg)        { message_stream << msg; return *this; };
		CApplogInput& operator<<(const std::string& msg) { message_stream << msg; return *this; };

	};

	class CApplogFinisher
	{
	public:
		void operator=(CApplogInput& input)
		{
			CApplog::GetInstance()->Log(input.m_elevel, input.info.str(),
				input.message_stream.str());
		}
	};
}



#endif