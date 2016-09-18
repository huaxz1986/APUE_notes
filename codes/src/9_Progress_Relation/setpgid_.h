/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 setpgid 函数的用法
 *
 */
#ifndef SETPGID_
#define SETPGID_
#include<unistd.h>

/*!
 * \brief My_setpgid : 包装了 setpgid 函数
 * \param pid : 传递给 setpgid 函数的 pid 参数
 * \param pgid : 传递给 setpgid 函数的 pgid 参数
 * \return : 返回了 setpgid 函数的值
 */
int My_setpgid(pid_t pid,pid_t pgid);

/*!
 * \brief test_setpgid : 测试 setpgid 函数
 */
void test_setpgid();
#endif // SETPGID_

