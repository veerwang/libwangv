#if !defined(INCLUDED_FUNCTIONS_HPP)
#define INCLUDED_FUNCTIONS_HPP  1

/*
 * =====================================================================================
 *
 *       Filename:  functionstemplate.hpp
 *
 *    Description:  保存一些神奇有用的模板 
 *
 *        Version:  1.0
 *        Created:  2015年02月13日 11时19分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <sstream>

namespace WangV
{
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  NumberToString 
 *  Description:  将任意的数字转换成为字符串 
 *        input:  数字
 *       output:  std::string类型的字符串
 * =====================================================================================
 */
template <typename T>
std::string NumberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  StringToNumber 
 *  Description:  将字符串转换成为相应的数字
 *        input:  std::string类型的字符串
 *       output:  对于的数字 
 * =====================================================================================
 */
template <typename T>
std::string StringToNumber ( const std::string &Text )
{
	std::istringstream ss(Text);
	T result;	
	return ss >> result ? result : 0; 
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  deletep 
 *  Description:  结构相应的类型指针 
 *        input:  需要进行解构的类型指针 
 * =====================================================================================
 */
template <typename T>
inline void deletep(T *p)
{
	if ( p != nullptr )
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
inline void deletearray(T *p)
{
	if ( p != nullptr )
	{
		delete[] p;
		p = nullptr;
	}
}


}
#endif /* !defined(INCLUDED_FUNCTIONS_HPP) */
