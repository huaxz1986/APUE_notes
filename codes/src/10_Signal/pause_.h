/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 pause 函数的用法
 *
 */
#ifndef PAUSE_
#define PAUSE_


/*!
 * \brief My_pause : 包装了 pause 函数
 * \return : 返回 pause 函数的值
 */
int My_pause(void);
/*!
 * \brief test_pause : 测试 pause 函数的用法
 */
void test_pause();
#endif // PAUSE_

