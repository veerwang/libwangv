/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/26/2017 09:25:35 PM
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

#include <threadtemplate.h> 
#include <singletontemplate.h> 
#include <pimpltemplate.h>
#include <functionstemplate.h>
#include <processcommunication.h>
#include <logcatdisplay.h>
#include <shellcommand.h> 

#include <wangvlib.h>
#include <keymap.h>

#include "base.h" 


class ModifyDisplayPolicy 
{
public:
	char* displaycore(const char *file, int level,const char * func, int line, const char *msg)
	{
		const char *c = "IWEDX";
		char timechar[64];
		const char *datetime_format = "%Y-%m-%d %H:%M:%S";
		time_t meow = time( NULL );
		strftime( timechar, 64, datetime_format, localtime(&meow) );
		sprintf(m_inside_msg,"[%d]===>[%s]%s:%s:%d %c  %s",(int)getpid(),timechar,file,func,line,c[level],msg);
		return m_inside_msg;
	}
protected:
	char m_inside_msg[1024];
};

typedef WangV::LogcatDisplay<ModifyDisplayPolicy> MyLog;

class deviceinput : public WangV::Singleton<deviceinput>
{
	public:
		~deviceinput()
		{
			MyLog *logcat = MyLog::Instance();
			logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"deviceinput %s","destroy");
		}

		void version()
		{
			WangV::Logcat *logcat = WangV::Logcat::Instance();
			logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"deviceinput %s","v1.0.0");
		}

	private:
		ENABLE_SINGLETON(deviceinput)
};

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  MyPolicy 
 *  Description:  自定义线程的执行函数 
 * =====================================================================================
 */
template<typename T>
class MyPolicy
{
	public:
		void Run()
		{
			MyLog *logcat = MyLog::Instance();
			logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"pthread %s","kevin");
		}
};

template< typename T >
class DoProcess 
{
public:
	int coreprocess(char *buf) 
	{
		WangV::Logcat *logcat = WangV::Logcat::Instance();
		logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"Server Info %s",buf);
		return 0;
	}
};

// 函数主体 

struct BasePara
{
	struct option longopts[3] =  
	{
		{ "server",0,NULL,'s' },
		{ "mdoc",0,NULL,'m' },
		{ "help",0,NULL,'h' },
	};
};


class BaseShellCmd 
{
public:
	void CodeProcess(int opt)
	{
		MyLog *logcat = MyLog::Instance();
		switch ( opt )
		{
			case 's':
				{
					MyLog *logcat = MyLog::Instance();
					logcat->log_module_init(NULL);
					logcat->log_module_level(WangV::Logcat::LOG_ERROR);
					logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"info %s","kevin");
					WangV::InitKey();
					char key = 0;

					WangV::ThreadHost<MyPolicy>*  pbasethread; 
					pbasethread = new WangV::ThreadHost<MyPolicy>();
					pbasethread->Set_Interval_Second(1);
					pbasethread->Start();

					WangV::encrypt_file("test.dat","1.enc");
					WangV::decrypt_file("1.enc","1.dec");

					deviceinput *di = deviceinput::Instance();
					di->version();

					Base* base = new Base;
					base->m_id.set(120);
					base->m_name.set("kevin");
					std::cout<<base->m_id.get()<<std::endl;
					std::cout<<base->m_name.get()<<std::endl;
					WangV::deletep(base);

					WangV::ProcessCommunicationServer<DoProcess> pc;
					if ( pc.init() )
						logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"Server Init OK");

					while ( key != KEY_ESC )
					{
						usleep(1000);
						key = WangV::GetPCKey();
						pc.doprocess();
					}

					if ( pbasethread != NULL )	
					{
						pbasethread->Stop();
						WangV::deletep(pbasethread);
					}

					logcat->log_module_destroy();

					WangV::RestoreKey();
					pc.release();
				}
				break;
			case 'm':
				{
					WangV::module_document();
				}
				break;
			case 'h':
				{
				}
				break;
			case '?':
				logcat->log_module_write((WangV::Logcat::LOG_INFO),__FILE__,__FUNCTION__,__LINE__,"???");
				break;
		}
	}
};

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	std::cout<<"Programe Version: "<<WangV::NumberToString(1.0)<<std::endl;		// 注意这个函数
	std::cout<<WangV::get_version()<<std::endl;

	WangV::ShellCommand<BaseShellCmd,BasePara> shellcmd;				// 注意这种方式可以推广
	shellcmd.Analyze(argc,argv,"smh?");						// 注意这个地方容易被忽略

	char ips[4][4] = {0};
	WangV::get_ip_segment("192.268.1.2",ips);					// 注意，这个是一个指向４个字符的二维数组
	for (int i=0;i<4;i++)
	{
		printf("IP %d segment: %s\n",i+1,ips[i]);
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
