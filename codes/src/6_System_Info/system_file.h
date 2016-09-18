/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第六章：系统数据文件和信息。
 *
 * 这里是访问系统数据文件的相关函数的测试。
 *
 */
#ifndef SYSTEM_FILE
#define SYSTEM_FILE
#include<pwd.h>
#include<shadow.h>
#include<grp.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<netdb.h>

/*!
 * \brief My_getpwuid ： 包装了 getpwuid  函数
 * \param uid : 传递给  getpwuid 函数的  uid 参数
 * \return : 返回 getpwuid 函数的值
 */
struct passwd* My_getpwuid(uid_t uid);
/*!
 * \brief My_getpwnam ： 包装了 getpwnam 函数
 * \param name : 传递给 getpwnam 函数的  name 参数
 * \return : 返回 getpwnam 函数的值
 */
struct passwd* My_getpwnam(const char*name);
/*!
 * \brief My_getpwent ： 包装了 getpwent 函数
 * \return : 返回 getpwent 函数的值
 */
struct passwd *My_getpwent(void);

/*!
 * \brief My_getspnam ： 包装了 getspnam 函数
 * \param name : 传递给 getspnam 函数的 name 参数
 * \return : 返回  getspnam 函数的值
 */
struct spwd *My_getspnam(const char*name);
/*!
 * \brief My_getspent ： 包装了 getspent 函数
 * \return : 返回 getspent 函数的值
 */
struct spwd *My_getspent(void);

/*!
 * \brief My_getgrgid ： 包装了 getgrgid 函数
 * \param gid : 传递给 getgrgid 函数的 gid 参数
 * \return : 返回 getgrgid 函数的值
 */
struct group* My_getgrgid(gid_t gid);
/*!
 * \brief My_getgrnam ： 包装了 getgrnam 函数
 * \param name : 传递给 getgrnam 函数的 name 参数
 * \return : 返回 getgrnam 函数的值
 */
struct group* My_getgrnam(const char* name);
/*!
 * \brief My_getgrent ： 包装了 getgrent 函数
 * \return : 返回 getgrent 函数的值
 */
struct group *My_getgrent(void);

/*!
 * \brief My_getgroups ： 包装了 getgroups 函数
 * \param gidsetsize : 传递给 getgroups 函数的 gidsetsize 参数
 * \param grouplist : 传递给 getgroups 函数的 grouplist 参数
 * \return : 返回 getgroups 函数的值
 */
int My_getgroups(int gidsetsize,gid_t grouplist[]);
/*!
 * \brief My_setgroups ： 包装了 setgroups 函数
 * \param ngroups : 传递给 setgroups 函数的 ngroups 参数
 * \param grouplist : 传递给 setgroups 函数的 grouplist 参数
 * \return : 返回 setgroups 函数的值
 */
int My_setgroups(int ngroups,const gid_t grouplist[]);
/*!
 * \brief My_initgroups ： 包装了 initgroups 函数
 * \param username : 传递给 initgroups 函数的 username 参数
 * \param basegid : 传递给 initgroups 函数的 basegid 参数
 * \return : 返回 initgroups 函数的值
 */
int My_initgroups(const char *username, gid_t basegid);

/*!
 * \brief My_gethostent ： 包装了 gethostent 函数
 * \return : 返回 gethostent 函数的值
 */
struct hostent * My_gethostent(void);

/*!
 * \brief My_uname ： 包装了 uname 函数
 * \param name : 传递给 uname 函数的 name 参数
 * \return : 返回 uname 函数的值
 */
int My_uname(struct utsname *name);
/*!
 * \brief My_gethostname ： 包装了 gethostname 函数
 * \param name : 传递给 gethostname 函数的 name 参数
 * \param namelen : 传递给 gethostname 函数的 namelen 参数
 * \return : 返回 gethostname 函数的值
 */
int My_gethostname(char *name,int namelen);

/*!
 * \brief print_passwd : 打印 passwd 结构
 * \param data : 指向 passwd 结构的指针
 */
void print_passwd(const struct passwd* data);
/*!
 * \brief print_spwd : 打印 spwd 结构
 * \param data : 指向 spwd 结构的指针
 */
void print_spwd(const struct spwd* data);
/*!
 * \brief print_group : 打印 group 结构
 * \param data : 指向 group 结构的指针
 */
void print_group(const struct group* data);
/*!
 * \brief print_utsname : 打印 utsname 结构
 * \param data : 指向 utsname 结构的指针
 */
void print_utsname(const struct utsname* data);
/*!
 * \brief print_hostent : 打印 hostent 结构
 * \param data : 指向 hostent 结构的指针
 */
void print_hostent(const struct hostent* data);

/*!
 * \brief _test_passwd : 测试 struct passwd 相关的函数
 */
void _test_passwd();
/*!
 * \brief _test_shadow : 测试 struct spwd 相关的函数
 */
void _test_shadow();
/*!
 * \brief _test_group : 测试 struct group 相关的函数
 */
void _test_group();
/*!
 * \brief _test_attach_groups : 测试附属组ID 相关的函数
 */
void _test_attach_groups();
/*!
 * \brief _test_host : 测试主机名和 host 相关的函数
 */
void _test_host();

/*!
 * \brief test_system_file : 测试系统数据文件相关的函数
 */
void test_system_file();

#endif // SYSTEM_FILE

