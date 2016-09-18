/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 times 函数的用法 （它用于获取进程以及已经终止子进程的运行时间）
 *
 */
#ifndef PROGRESS_TIMES_
#define PROGRESS_TIMES_
#include<sys/times.h>

/*!
 * \brief My_times : 包装了 times 函数
 * \param buf : 传递给 times 函数的参数
 * \return : 返回 times 函数的值
 */
clock_t My_times(struct tms *buf);

/*!
 * \brief clock_2_second : 将 clock_t 转换成秒
 * \param clk : clock_t 数量
 * \return ： 对应的秒数
 */
long clock_2_second(clock_t clk);
/*!
 * \brief print_tms ： 打印 struct tms 结构
 * \param tm : struct ms 的指针
 */
void print_struct_tms(const struct tms*tm);

/*!
 * \brief test_times : 测试 times 函数
 */
void test_progress_times();
#endif // PROGRESS_TIMES_

