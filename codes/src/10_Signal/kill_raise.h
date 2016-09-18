/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 kill 函数、raise 函数的用法
 *
 */
#ifndef KILL_RAISE
#define KILL_RAISE
#include<signal.h>

/*!
 * \brief My_kill : 包装了 kill 函数
 * \param pid : 传递给 kill 函数的 pid 参数
 * \param signo : 传递给 kill 函数的 signo 参数
 * \return : 返回 kill 函数的值
 */
int My_kill(pid_t pid,int signo);
/*!
 * \brief My_raise : 包装了 raise 函数
 * \param signo : 传递给 raise 函数的 signo 参数
 * \return : 返回 raise 函数的值
 */
int My_raise(int signo);

/*!
 * \brief test_kill_raise : 测试  kill 函数、raise 函数
 */
void test_kill_raise();
#endif // KILL_RAISE

