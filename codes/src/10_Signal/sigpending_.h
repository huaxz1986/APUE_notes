/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigpending 函数的用法
 *
 */
#ifndef SIGPENDING_
#define SIGPENDING_
#include<signal.h>

/*!
 * \brief My_sigpending : 包装了 sigpending 函数
 * \param set : 传递给 sigpending 函数的 set 参数
 * \return  : 返回 sigpending 函数的值
 */
int My_sigpending(sigset_t *set);
/*!
 * \brief print_progress_pending_sigset : 打印进程当前的未决的信号集
 */
void print_progress_pending_sigset();
/*!
 * \brief test_sigpending :测试 sigpending 函数的用法
 */
void test_sigpending();


#endif // SIGPENDING_

