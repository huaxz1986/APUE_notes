/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 setuid 函数、 seteuid 函数、 setgid 函数、setegid 函数 、getlogin 函数的用法
 *
 */
#ifndef SETUID_SETEUID
#define SETUID_SETEUID
#include<unistd.h>

/*!
 * \brief My_setuid : 包装了 etuid 函数
 * \param uid : 传递给 etuid 函数的 uid 参数
 * \return : 返回 etuid 函数的值
 */
int My_setuid(uid_t uid);
/*!
 * \brief My_setgid : 包装了 setgid 函数
 * \param gid : 传递给 setgid 函数的 gid 参数
 * \return : 返回 setgid 函数的值
 */
int My_setgid(gid_t gid);
/*!
 * \brief My_seteuid : 包装了 seteuid 函数
 * \param uid : 传递给 seteuid 函数的 uid 参数
 * \return : 返回 seteuid 函数的值
 */
int My_seteuid(uid_t uid);
/*!
 * \brief My_setegid : 包装了 setegid 函数
 * \param gid : 传递给 setegid 函数的 gid 参数
 * \return : 返回 setegid 函数的值
 */
int My_setegid(gid_t gid);
/*!
 * \brief My_getlogin : 包装了 getlogin 函数
 * \return : 返回 getlogin 函数的值
 */
char* My_getlogin(void);

/*!
 * \brief test_setuid_seteuid : 测试 setuid/seteuid/setgid/setegid/getlogin 等函数
 */
void test_setuid_seteuid();
#endif // SETUID_SETEUID

