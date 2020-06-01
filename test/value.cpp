/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年06月01日 
 *       Revision:  1 
 *       Compiler:  gcc
 *
 *         Author:  kevin.wang 
 *   Organization:  
 *
 * =====================================================================================
 */

#include 	<cstdlib>
#include 	<cstdio>
#include 	<iostream>
#include 	<functionstemplate.h>

/* 可以采用继承的方式进行数据的改写 */
/* 将全局的数据进行改写 */
template<typename T>
class MyValue : public WangV::Value<T> {
public:
	inline void set(const T value) {
		T v = value + 1;
		WangV::Value<T>::set(v);
	}
};

int main(int argc, const char *argv[]) {
	std::cout << "value template test" << std::endl;

	WangV::Value<int> id;
	id.set(10);
	std::cout << id.get() << std::endl;

	MyValue<int> myid;
	myid.set(10);
	std::cout << myid.get() << std::endl;

	return EXIT_SUCCESS;
}
