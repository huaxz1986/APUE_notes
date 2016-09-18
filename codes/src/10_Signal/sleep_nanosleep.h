/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sleep 函数、 nano_sleep 函数、 clock_nanosleep 函数的用法
 *
 */
#ifndef SLEEP_NANOSLEEP
#define SLEEP_NANOSLEEP
#include<time.h>

/*!
 * \brief My_sleep : 包装了 sleep 函数
 * \param seconds : 传递给 sleep 函数的 seconds 参数
 * \return  : 返回 sleep 函数的值
 */
unsigned int My_sleep(unsigned int seconds);
/*!
 * \brief My_nanosleep : 包装了 nanosleep 函数
 * \param reqtp : 传递给 nanosleep 函数的  reqtp 参数
 * \param remtp : 传递给 nanosleep 函数的 remtp  参数
 * \return  : 返回 nanosleep 函数的值
 */
int My_nanosleep(const struct timespec*reqtp,struct timespec *remtp);
/*!
 * \brief My_clock_nanosleep : 包装了 clock_nanosleep 函数
 * \param clock_id : 传递给 clock_nanosleep 函数的  clock_id 参数
 * \param flags : 传递给 clock_nanosleep 函数的 flags 参数
 * \param reqtp : 传递给 clock_nanosleep 函数的 reqtp 参数
 * \param remtp : 传递给 clock_nanosleep 函数的  remtp 参数
 * \return  : 返回 clock_nanosleep 函数的值
 */
int My_clock_nanosleep(clockid_t clock_id,int flags,
            const struct timespec *reqtp,struct timespec *remtp);

/*!
 * \brief test_sleep_nanosleep :测试 sleep 函数、 nano_sleep 函数、 clock_nanosleep 函数的用法
 */
void test_sleep_nanosleep();
#endif // SLEEP_NANOSLEEP

