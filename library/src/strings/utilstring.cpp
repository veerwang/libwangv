/*
 * =====================================================================================
 *
 *       Filename:  utilstring.cpp
 *
 *    Description:  utils功能 
 *
 *        Version:  1.0
 *        Created:  2018年11月23日 13时34分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  LiLin-Tech
 *   Organization:  GNU
 *
 * =====================================================================================
 */
#include "utilstring.h"

#include <standard.h>

#include "logcatdisplay.h" 

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
 *--------------------------------------------------------------------------------------
 *       Class:  Utilstring
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Utilstring::Utilstring ()
{
}  /* -----  end of method Utilstring::Utilstring  (constructor)  ----- */

Utilstring::~Utilstring ()
{
}  /* -----  end of method Utilstring::Utilstring  (destructor)  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  IP_Segment 
 *  Description:  将一个IP地址，转换成为一个二维数组 
 * =====================================================================================
 */
void Utilstring::IP_Segment(const char* ip,char (*segment)[4])
{
	SegmentIP sip(ip);

	for (int i=0;i<4;i++)
		sprintf(segment[i],"%s",sip.get_ip(i).c_str());
}
