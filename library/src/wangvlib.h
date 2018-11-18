#if !defined(INCLUDED_WANGVLIB_H)
#define INCLUDED_WANGVLIB_H  1

/*
 * =====================================================================================
 *
 *       Filename:  main.h
 *
 *    Description:  模块的接口文件，目标是兼容C语言 
 *
 *        Version:  1.0
 *        Created:  2014年12月02日 10时18分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  LiLin-Tech
 *   Organization:  GNU
 *
 * =====================================================================================
 */
namespace WangV {

/*　模块信息功能  */
const char* get_version();
void module_document();

/* key按键检测功能 */
void InitKey();
void RestoreKey();
char GetPCKey();

/* encrypt加密解密功能 */
int rename_file(const char* src,const char* des);
int copy_file(const char* src,const char* des);
int unlink_file(const char* file);
void encrypt_file(const char* src,const char* des);
void decrypt_file(const char* src,const char* des);

/* 将一个IP地址的４个段，转换为４个字符串，注意这种声明方式 */
void get_ip_segment(const char* ip,char (*segment)[4]);
}

#endif /* !defined(INCLUDED_WANGVLIB_H) */
