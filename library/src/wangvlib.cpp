/*
 * =====================================================================================
 *
 *       Filename:  wangvlib.cpp
 *
 *    Description:  模块的实现代码 
 *
 *        Version:  1.0
 *        Created:  2014年12月02日 09时21分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  LiLin-Tech
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include "wangvlib.h"

#include <standard.h>

#include "logcatdisplay.h" 

namespace WangV {

static const char PROJ_VERSION[] = {"V1.02"};

class SegmentIP
{
	public:
		SegmentIP(std::string ip);
		~SegmentIP();

		std::string get_ip(int p);
	private:
		void segment_ip(std::string IP);

	private:
		std::string	m_ip;
		std::string	m_sip[4];
};

SegmentIP::SegmentIP(std::string ip) 
{ 
	m_ip = ip; 
	segment_ip(m_ip); 
}

SegmentIP::~SegmentIP() 
{

}
		
std::string SegmentIP::get_ip(int p) 
{ 
	return m_sip[p]; 
}

void SegmentIP::segment_ip(std::string IP)
{
	const static int LENGTH = 4;
	std::string dot(".");
	size_t dotp = 0;
	size_t lp   = 0;
	for ( int i=0;i<LENGTH;i++ )
	{ 	
		dotp = IP.find(dot,dotp+1);
		if ( dotp != std::string::npos )
		{
			m_sip[i] = IP.substr(lp,dotp-lp);
			lp = dotp + 1;
		}
		else
			m_sip[i] = IP.substr(lp);
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_ip_segment 
 *  Description:  将一个IP地址，转换成为一个二维数组 
 * =====================================================================================
 */
void get_ip_segment(const char* ip,char (*segment)[4])
{
	SegmentIP sip(ip);

	for (int i=0;i<4;i++)
		sprintf(segment[i],"%s",sip.get_ip(i).c_str());
}

/* module function  */
void module_document()
{
	Logcat *logcat = Logcat::Instance();
	logcat->log_module_write(Logcat::LOG_INFO,"","",0,"\t\tlibrary of wangvlib document");
	logcat->log_module_write(Logcat::LOG_INFO,"","",0,"\n");
	logcat->log_module_write(Logcat::LOG_INFO,"","",0,"logcat module: do the debug log");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_version 
 *  Description:  获得模块的版本信息 
 * =====================================================================================
 */
const char* get_version()
{
	return PROJ_VERSION;
}

void __attribute__ ((constructor)) init_module()
{
	Logcat *logcat = Logcat::Instance();
	logcat->log_module_init(NULL);
	logcat->log_module_level(Logcat::LOG_ERROR);
	logcat->log_module_write(Logcat::LOG_DEBUG,__FILE__,__FUNCTION__,__LINE__,"init module %s","wangvlib");
}

void __attribute__ ((destructor)) release_module()
{
	Logcat *logcat = Logcat::Instance();
	logcat->log_module_write(Logcat::LOG_DEBUG,__FILE__,__FUNCTION__,__LINE__,"destruct module %s","wangvlib");
	logcat->log_module_destroy();  
}

}
