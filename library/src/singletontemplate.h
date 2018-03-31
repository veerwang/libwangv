#ifndef SINGLETONTEMPLATE_H
#define SINGLETONTEMPLATE_H

/*
 * =====================================================================================
 *
 *       Filename:  singletontemplate.h
 *
 *    Description:  以模板的方式实现单体类的基类
 *
 *        Version:  1.0
 *        Created:
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:
 *        Company:
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <standard.h>

namespace WangV
{

template <typename T>
class Singleton
{
	public:
		static T* Instance();

	protected:

	private:
		static std::unique_ptr<T>      m_Instance;		/* 仅仅是声明 */
};

template <typename T>
std::unique_ptr<T> Singleton<T>::m_Instance;                              /* 定义 */

template <typename T>
T* Singleton<T>::Instance()
{
	if 	( m_Instance.get() == 0 )
	{
		m_Instance.reset( new(std::nothrow) T() );
	}
	return m_Instance.get();
}
									/* 以下的宏定义要非常注意 */
#define ENABLE_SINGLETON(CLASS) friend class Singleton<CLASS>; friend class std::unique_ptr<CLASS>;

}

#endif /* SINGLETONTEMPLATE_H */
