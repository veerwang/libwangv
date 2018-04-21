#if !defined(INCLUDED_BASE_H)
#define INCLUDED_BASE_H  1

/*
 * =====================================================================================
 *
 *       Filename:  base.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/2017 05:04:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), wwei@landicorp.com
 *        Company:  Landicorp
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <string>
#include <pimpltemplate.h>
#include <functionstemplate.h>


class InterfacePublic
{
	public:
		InterfacePublic () : m_id(0),m_name("wangwei")
		{;}

		WangV::Value<int> 	   	m_id;
		WangV::Value<std::string> 	m_name;
};

class Base : public InterfacePublic
{
	public:
		Base ();                                       /* constructor */
		~Base ();                                      /* destructor  */

	protected:
		WangV::PimplOf<Base>::Type 	m_Imple;

	private:

}; /* -----  end of class Base  ----- */

#endif /* !defined(INCLUDED_BASE_H) */
