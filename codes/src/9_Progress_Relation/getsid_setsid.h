/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 getsid 函数、setsid 函数的用法
 *
 */
#ifndef GETSID_SETSID
#define GETSID_SETSID
#include<unistd.h>

/*!
 * \brief My_setsid : 包装了 setsid 函数的值
 * \return : 返回 setsid 函数的值
 */
pid_t My_setsid(void);
/*!
 * \brief My_getsid : 包装了 getsid 函数的值
 * \param pid : 传递给 getsid 函数的 pid 参数
 * \return : 返回 getsid 函数的值
 */
pid_t My_getsid(pid_t pid);

/*!
 * \brief test_getsid_setsid :测试 getsid 函数、setsid 函数的用法
 */
void test_getsid_setsid();
#endif // GETSID_SETSID

