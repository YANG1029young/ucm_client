/********************************************************************************
**    Copyright (c) by Hinge-Tech R&D Center.
**
**    CONFIDENTIAL and PROPRIETARY UNPUBLISHED SOURCE CODE.
**    Disclosure, use or reproduction is prohibited without authorization.
**        
*********************************************************************************
**    File  : log_extend.h
**    Target: the file is used for define an abstraction layer for the print log
**            the function is encapsulation the encapsulation of the underlying 
**            log driver.
**    Author: aijun.yang
**    Date  : 2019-01-17
**          
******************************************************************************/

#ifndef _LOG_EXTEND_
#define _LOG_EXTEND_
/******************************************************************************
**    INCLUDES
******************************************************************************/
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "ara/log/common.h"
#include "ara/log/logger.h"
#include "ara/log/logstream.h"

namespace ara {
namespace per {
	
using  namespace ara::log;
using SLogLevel = LogLevel;
#define kOff   	 (LogLevel::kOff)
#define kFatal   (LogLevel::kFatal)
#define kError   (LogLevel::kError)
#define kWarn    (LogLevel::kWarn)
#define kInfo    (LogLevel::kInfo)
#define kDebug   (LogLevel::kDebug)
#define kVerbose (LogLevel::kVerbose)


	
#define PRINT_STDOUT(fmt, ...) \
	    printf("[%s][%d]" fmt "\r\n", __FILE__, __LINE__, ##__VA_ARGS__);
/******************************************************************************
**	  CLASSES/FUNCTIONS DEFINITIONS
******************************************************************************/
class LogExtend
{
	public:
		virtual ~LogExtend();
		LogExtend(std::string szAppName);
		static LogExtend * getLogExtenObject(std::string szAppName);
		int  logInit(SLogLevel eLogLevel);
		void setLogLevel(SLogLevel eLogLevel);
		void logPrint(SLogLevel eLog, std::string file, int line,char *fmt,...);
	private:
		LogExtend(std::string szAppName, int iLogLevel);
		static LogExtend * mLogObj;
		static Logger      *mLogModule;
	public:
		std::string mLogExtendName;
		SLogLevel    mLogLevel;
};
		
}//phm
}//ara
#endif
