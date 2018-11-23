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
#include "strings/utilstring.h"

namespace WangV {

static const char PROJ_VERSION[] = {"V1.02"};


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_ip_segment 
 *  Description:  将一个IP地址，转换成为一个二维数组 
 * =====================================================================================
 */
void get_ip_segment(const char* ip,char (*segment)[4])
{
	Utilstring us;
	us.IP_Segment(ip,segment);
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
