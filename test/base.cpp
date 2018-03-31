/*
 * =====================================================================================
 *
 *       Filename:  base.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/2017 05:05:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), wwei@landicorp.com
 *        Company:  Landicorp
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include "base.h"
#include <wangvlib.h> 

#include <logcatdisplay.h>

namespace WangV
{
template<>
struct ImplOf<Base>
{
	int id;
};
}

Base::Base ()
{
	m_Imple->id = 10;
}

Base::~Base ()
{
	WangV::Logcat *logcat = WangV::Logcat::Instance();
	logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"id = %d destroy",m_Imple->id);
}
