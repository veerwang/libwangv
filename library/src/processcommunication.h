#if !defined(INCLUDED_PROCESSCOMMUNICATION_H)
#define INCLUDED_PROCESSCOMMUNICATION_H  1

/*
 * =====================================================================================
 *
 *       Filename:  processcommunication.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年10月11日 15时24分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  LiLin-Tech
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <standard.h>
#include "wangvlib.h"
#include "logcatdisplay.h" 

namespace WangV
{
/* 
 *	定义一个常量
 */
template <typename T>
struct ConstValue
{
	static const char* UNIX_DOMAIN;
};
template <typename T>
const char* ConstValue<T>::UNIX_DOMAIN = "/tmp/UNIX.domain";

/* ----- 服务端 ------ */

/* 
 * 	默认处理函数	
 */
template< typename T >
class DefaultServerProcess 
{
public:
	int coreprocess(char* buf) { return 0; }
};

template< template<typename T> class Process = DefaultServerProcess >
class ProcessCommunicationServer : public Process<class T>
{
public:
	ProcessCommunicationServer() { init_flag = false; accept_flag = false; }
	virtual ~ProcessCommunicationServer() {;}

public:
	bool init()
	{
		srv_addr.sun_family = AF_UNIX;
		strncpy(srv_addr.sun_path,ConstValue<T>::UNIX_DOMAIN,sizeof(srv_addr.sun_path)-1);  
		listen_fd = socket(PF_UNIX, SOCK_STREAM, 0); 
		if ( listen_fd  < 0 )
		{
			Logcat *logcat = Logcat::Instance();
			logcat->log_module_write(Logcat::LOG_ERROR,__FILE__,__FUNCTION__,__LINE__,"server sock create fail");
		}
		unlink(ConstValue<T>::UNIX_DOMAIN);
		int ret = bind(listen_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
		if ( ret == -1 )
		{
			Logcat *logcat = Logcat::Instance();
			logcat->log_module_write(Logcat::LOG_ERROR,__FILE__,__FUNCTION__,__LINE__,"cannot bind server socket: %s",strerror(errno));
			close(listen_fd);
			unlink(ConstValue<T>::UNIX_DOMAIN);
			return false;
		}

		//listen sockfd   
		ret = listen(listen_fd,1);
		if ( ret==-1 )
		{  
			Logcat *logcat = Logcat::Instance();
			logcat->log_module_write(Logcat::LOG_ERROR,__FILE__,__FUNCTION__,__LINE__,"cannot listen the client connect request: %s",strerror(errno));
			close(listen_fd);  
			unlink(ConstValue<T>::UNIX_DOMAIN);  
			return false;  
		}

		m_tv.tv_sec  = 0;
		m_tv.tv_usec = 1;

		init_flag = true;
		Logcat *logcat = Logcat::Instance();
		logcat->log_module_write(Logcat::LOG_DEBUG,__FILE__,__FUNCTION__,__LINE__,"Server Init OK");
		return true;
	}

	void release()
	{
		if ( init_flag == false ) return;
		close(listen_fd);
		Logcat *logcat = Logcat::Instance();
		logcat->log_module_write(Logcat::LOG_DEBUG,__FILE__,__FUNCTION__,__LINE__,"Server Close");
		unlink(ConstValue<T>::UNIX_DOMAIN);
	}

	void doprocess()
	{
		if ( accept_flag )
		{
			if ( !com_fd ) return ;
			static char recv_buf[1024];
			fd_set	mRDfd;

			FD_ZERO(&mRDfd);
			FD_SET(com_fd,&mRDfd);

			if ( select(com_fd+1,&mRDfd,NULL,NULL,&m_tv) <= 0 )
				usleep(1000);
			else
			{
				if ( !FD_ISSET(com_fd,&mRDfd) )
					usleep(1000);
				else
				{
					memset(recv_buf,0,1024);
					int num=read(com_fd,recv_buf,sizeof(recv_buf));  
					if ( num == 0 )
					{
						Logcat *logcat = Logcat::Instance();
						logcat->log_module_write(Logcat::LOG_DEBUG,__FILE__,__FUNCTION__,__LINE__,"ServerInfo: client close");
						close(com_fd);
					}
					else if ( num == -1 )
					{
						Logcat *logcat = Logcat::Instance();
						logcat->log_module_write(Logcat::LOG_ERROR,__FILE__,__FUNCTION__,__LINE__,"ServerInfo: client bad: %s",strerror(errno));
						close(com_fd);
					}
					else
					{
						this->coreprocess(recv_buf);
					}
				}
			}
		}
		else
		{
			fd_set	mRDfd;
			FD_ZERO(&mRDfd);
			FD_SET(listen_fd,&mRDfd);

			if ( select(listen_fd+1,&mRDfd,NULL,NULL,&m_tv) <= 0 )
				usleep(1000);
			else
			{
				if ( !FD_ISSET(listen_fd,&mRDfd) )
					usleep(1000);
				else
				{
					clt_addr_len = sizeof(clt_addr);
					com_fd=accept(listen_fd,(struct sockaddr*)&clt_addr,&clt_addr_len);
					if( com_fd < 0 )
					{
						Logcat *logcat = Logcat::Instance();
						logcat->log_module_write(Logcat::LOG_ERROR,__FILE__,__FUNCTION__,__LINE__,"cannot accept client connect request: %s",strerror(errno));
						close(listen_fd);  
						unlink(ConstValue<T>::UNIX_DOMAIN);  
						accept_flag = false;
						init_flag = false;
					}
					accept_flag = true;
				}
			}
		}
	}

private:
	int 		listen_fd;
	int 		com_fd;  
	struct 		sockaddr_un srv_addr;  
	struct 		sockaddr_un clt_addr;  
    	socklen_t 	clt_addr_len;  
	bool 		init_flag;
	bool 		accept_flag;
	struct timeval 	m_tv;
};

/* ----- 客户端 ------ */

template< typename T >
class DefaultClientProcess 
{
public:
	int connect_fd;  
	int coreprocess(int num,char* buf) { write(connect_fd,buf,num); return 0; }
};

template< template<typename T> class Process = DefaultClientProcess >
class ProcessCommunicationClient : public Process<class T>
{
public:
	ProcessCommunicationClient(){ init_flag = false; connect_flag = false; }
	virtual ~ProcessCommunicationClient(){;}
public:
	bool init()
	{
		this->connect_fd=socket(PF_UNIX,SOCK_STREAM,0);  
		if(this->connect_fd<0)  
		{  
			Logcat *logcat = Logcat::Instance();
			logcat->log_module_write(Logcat::LOG_ERROR,__FILE__,__FUNCTION__,__LINE__,"cannot create communication socket: %s",strerror(errno));
			return false;  
		}     
		srv_addr.sun_family=AF_UNIX;  
		strcpy(srv_addr.sun_path,ConstValue<T>::UNIX_DOMAIN);  
		init_flag = true;
		return true;
	}

	void connect_server()
	{
		int ret = connect(this->connect_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));  
		if( ret == -1 )  
		{
			Logcat *logcat = Logcat::Instance();
			logcat->log_module_write(Logcat::LOG_ERROR,__FILE__,__FUNCTION__,__LINE__,"cannot connect to the server: %s",strerror(errno));
			close(this->connect_fd);  
			return;
		}
		connect_flag = true;  
	}

	void doprocess(char* buf)
	{
		if ( init_flag == false || connect_flag == false ) return;
		this->coreprocess(strlen(buf),buf);
	}

	void release()
	{
		if ( init_flag == false ) return;
		close(this->connect_fd);  
		Logcat *logcat = Logcat::Instance();
		logcat->log_module_write(Logcat::LOG_DEBUG,__FILE__,__FUNCTION__,__LINE__,"Client Close");
		init_flag    = false;
		connect_flag = false;
	}
private:
	int 	ret;  
	struct 	sockaddr_un srv_addr;  
	bool 	init_flag;
	bool 	connect_flag;
};
}

#endif /* !defined(INCLUDED_PROCESSCOMMUNICATION_H) */
