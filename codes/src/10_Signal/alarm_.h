/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 alarm 函数的用法
 *
 */
#ifndef ALARM_
#define ALARM_

/*!
 * \brief My_alarm : 包装了 alarm 函数
 * \param seconds : 传递给 alarm 函数的 seconds 参数
 * \return : 返回 alarm 函数的值
 */
unsigned int My_alarm(unsigned int seconds);

/*!
 * \brief test_alarm : 测试 alarm 函数的用法
 */
void test_alarm();
#endif // ALARM_

