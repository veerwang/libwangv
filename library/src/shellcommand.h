#if !defined(INCLUDED_SHELLCOMMAND_H)
#define INCLUDED_SHELLCOMMAND_H  1

/*
 * =====================================================================================
 *
 *       Filename:  shellcommand.h
 *
 *    Description:  保存的是命令行相关的代码 
 *
 *        Version:  1.0
 *        Created:  11/18/2017 05:14:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), wwei@landicorp.com
 *        Company:  Landicorp
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <standard.h>
#include "wangvlib.h"
#include "logcatdisplay.h"

namespace WangV
{

class DefaultShellCmd 
{
public:
	void CodeProcess(int opt)
	{
		switch ( opt )
		{
			case 'n':
				break;
			case 'h':
				break;
			case '?':
				break;
		}	
	}
};

struct DefaultPara
{
	struct option longopts[2] =  
	{
		{ "normal",0,NULL,'n' },
		{ "help",0,NULL,'h' },
	};
};

template< typename T = DefaultShellCmd, typename U = DefaultPara >
class ShellCommand : public T, public U
{
public:
	ShellCommand () {;}
	~ShellCommand () {;}

	int Analyze( int argc, char* argv[], const char* cmd)
	{
		int opt;
		while( ( opt = getopt_long(argc,argv,cmd,this->longopts,NULL) ) != -1 )
		{
			this->CodeProcess(opt);
		}
	}
};

}
#endif /* !defined(INCLUDED_SHELLCOMMAND_H) */
