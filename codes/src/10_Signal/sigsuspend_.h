/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigsuspend 函数的用法
 *
 */
#ifndef SIGSUSPEND_
#define SIGSUSPEND_

#include<signal.h>
/*!
 * \brief My_sigsuspend ：包装了 sigsuspend 函数
 * \param sigmask : 传递给 sigsuspend  函数的 sigmask 参数
 * \return : 返回 sigsuspend  函数的值
 */
int My_sigsuspend(const sigset_t *sigmask);

void test_sigsuspend();

#endif // SIGSUSPEND_

