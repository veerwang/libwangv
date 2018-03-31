#if !defined(INCLUDED_LOGCATDISPLAY_H)
#define INCLUDED_LOGCATDISPLAY_H  1

/*
 * =====================================================================================
 *
 *       Filename:  logcatdisplay.h
 *
 *    Description:  用于编写日志显示功能
 *
 *        Version:  1.0
 *        Created:  2017年11月01日 19时34分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  Landicorp 
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <standard.h>
#include <singletontemplate.h> 
#include <functionstemplate.h>

#include "wangvlib.h"

namespace WangV
{

class DefaultDisplayPolicy 
{
public:
	void displaycore()
	{
		;
	}
};

template <typename Display = DefaultDisplayPolicy >
class LogcatDisplay : public Singleton<LogcatDisplay<Display> >, public Display
{
public:
	LogcatDisplay() : log_device_fp(NULL), log_level(5) , m_msg(NULL)
	{ 
		m_msg 		= new char[LOG_MAX_MSG_LEN];
		m_timechar	= new char[64];
	}
	~LogcatDisplay() { deletearray(m_msg); deletearray(m_timechar); }

public:
	void log_module_init(const char *device)
	{
		log_device_fp = !device ? stdout : fopen((const char *)device, "a+");
	}

	void log_module_destroy()
	{
		if (log_device_fp != stdout) fclose(log_device_fp);
	}

	void log_module_level(int level)
	{
		log_level = level;
	}

	const char* log_set_color(int level, int is_end)
	{
		if (log_device_fp == stdout) {
			if (is_end) {
				return RESET_COLOR;
			} else {
				switch (level) {
					case 0 : return FG_DEFAULT; break;
					case 1 : return FG_YELLOW; break;
					case 2 : return FG_RED; break;
					case 3 : return FG_BLUE; break;
					case 4 : return FG_CYAN; break;
					default : return FG_WHITE; break;
				}
			}
		}
		return "";
	}

	void log_module_write(int level, const char *file, const char * func, int line, const char *fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		vsnprintf(m_msg, LOG_MAX_MSG_LEN, fmt, ap);
		log_add(level, file, func, line, m_msg);
		va_end(ap);
		return;
	}

private:
	void log_add(int level, const char *file, const char * func, int line, const char *msg)
	{
		if ( level < log_level || level < 0 ) return;

		const char *c = "IWEDX";
		const char *datetime_format = "%Y-%m-%d %H:%M:%S";
		time_t meow = time( NULL );

		strftime( m_timechar, 64, datetime_format, localtime(&meow) );
		fprintf(log_device_fp, "%s%s[%d][%s(%s):%d] %c, %s%s\n",log_set_color(level, 0) , m_timechar, (int)getpid(), file, func, line, c[level], msg ,log_set_color(level, 1));

		this->displaycore();
	}


public:
	static const int LOG_ALL; 
	static const int LOG_ERROR;
	static const int LOG_WARN;
	static const int LOG_DEBUG;
	static const int LOG_INFO;

private:
	ENABLE_SINGLETON(LogcatDisplay)

private:
	FILE *log_device_fp  ;
	int   log_level      ;
	char* m_msg	     ;
	char* m_timechar     ;

	static const int LOG_MAX_MSG_LEN;

	static const char* FG_WHITE;
	static const char* FG_RED;
	static const char* FG_RED_BOLD;
	static const char* FG_GREEN;
	static const char* FG_GREEN_BOLD;
	static const char* FG_YELLOW; 
	static const char* FG_YELLOW_BOLD;
	static const char* FG_BLUE;
	static const char* FG_BLUE_BOLD;
	static const char* FG_CYAN;
	static const char* FG_CYAN_BOLD;
	static const char* FG_DEFAULT;
	static const char* BG_RED;
	static const char* BG_GREEN;
	static const char* BG_BLUE;
	static const char* BG_DEFAULT;
	static const char* RESET_COLOR;
};


template < typename Display>
const int LogcatDisplay<Display>::LOG_MAX_MSG_LEN 	= 	4096;


template < typename Display>
const int LogcatDisplay<Display>::LOG_ALL 		= 	1		;


template < typename Display>
const int LogcatDisplay<Display>::LOG_ERROR		= 	2		;


template < typename Display>
const int LogcatDisplay<Display>::LOG_WARN		= 	3		;


template < typename Display>
const int LogcatDisplay<Display>::LOG_DEBUG		= 	4		;


template < typename Display>
const int LogcatDisplay<Display>::LOG_INFO		= 	5		;


template < typename Display>
const char* LogcatDisplay<Display>::FG_WHITE		= 	"\x1B[0;m"	;   /* white */


template < typename Display>
const char* LogcatDisplay<Display>::FG_RED    	= 	"\033[0;31m"	;   /* 0 -> normal ; 31 -> red */


template < typename Display>
const char* LogcatDisplay<Display>::FG_RED_BOLD  	=	"\033[1;31m" 	;   /* 1 -> bold ; 31 -> red */


template < typename Display>
const char* LogcatDisplay<Display>::FG_GREEN   	=	"\033[0;32m"  	;   /* 4 -> underline ; 32 -> green */


template < typename Display>
const char* LogcatDisplay<Display>::FG_GREEN_BOLD	=       "\033[1;32m"	;


template < typename Display>
const char* LogcatDisplay<Display>::FG_YELLOW 	=       "\033[0;33m"  	;   /* 0 -> normal ; 33 -> yellow */


template < typename Display>
const char* LogcatDisplay<Display>::FG_YELLOW_BOLD	=	"\033[1;33m"	;


template < typename Display>
const char* LogcatDisplay<Display>::FG_BLUE  		=	"\033[0;34m"  	;   /* 9 -> strike ; 34 -> blue */


template < typename Display>
const char* LogcatDisplay<Display>::FG_BLUE_BOLD    	=	"\033[1;34m"	;


template < typename Display>
const char* LogcatDisplay<Display>::FG_CYAN   	=	"\033[0;36m"    ;   /* 0 -> normal ; 36 -> cyan */


template < typename Display>
const char* LogcatDisplay<Display>::FG_CYAN_BOLD	=	"\033[0;36m"	;


template < typename Display>
const char* LogcatDisplay<Display>::FG_DEFAULT  	=	"\033[39m"	;


template < typename Display>
const char* LogcatDisplay<Display>::BG_RED      	=	"\033[41m"	;


template < typename Display>
const char* LogcatDisplay<Display>::BG_GREEN    	=	"\033[42m"	;


template < typename Display>
const char* LogcatDisplay<Display>::BG_BLUE     	=	"\033[44m"	;


template < typename Display>
const char* LogcatDisplay<Display>::BG_DEFAULT  	= 	"\033[49m"	;


template < typename Display>
const char* LogcatDisplay<Display>::RESET_COLOR    	=	"\033[0m" 	;/* to flush the previous property */

typedef WangV::LogcatDisplay<> Logcat;
}

#endif /* !defined(INCLUDED_LOGCATDISPLAY_H) */
