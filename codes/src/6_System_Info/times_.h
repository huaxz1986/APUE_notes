/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第六章：系统数据文件和信息。
 *
 * 这里是时间相关函数的测试。
 *
 */
#ifndef TIMES_
#define TIMES_
#include<time.h>
#include<sys/time.h>


/*!
 * \brief My_time : 包装了 time 函数
 * \param calptr : 传递给 time 函数的 calptr 参数
 * \return : 返回 time 函数的值
 */
time_t My_time(time_t *calptr);
/*!
 * \brief My_clock_gettime : 包装了 clock_gettime 函数
 * \param clock_id : 传递给 clock_gettime 函数的 clock_id 参数
 * \param tsp : 传递给 clock_gettime 函数的 tsp 参数
 * \return : 返回 clock_gettime 函数的值
 */
int My_clock_gettime(clockid_t clock_id,struct timespec *tsp);
/*!
 * \brief My_clock_getres : 包装了 clock_getres 函数
 * \param clock_id : 传递给 clock_getres 函数的 clock_id 参数
 * \param tsp : 传递给  clock_getres 函数的 tsp 参数
 * \return : 返回 clock_getres 函数的值
 */
int My_clock_getres(clockid_t clock_id,struct timespec *tsp);
///*!
// * \brief My_clock_settime : 包装了 clock_settime 函数
// * \param clock_id : 传递给 clock_settime 函数的 clock_id 参数
// * \param tsp : 传递给 clock_settime 函数的 tsp 参数
// * \return : 返回 clock_settime 函数的值
// */
//int My_clock_settime(clockid_t clock_id,const struct timepsec *tsp);
/*!
 * \brief My_gettimeofday : 包装了 gettimeofday 函数
 * \param tp : 传递给 gettimeofday 函数的 tp 参数
 * \param tzp : 传递给 gettimeofday 函数的 tzp 参数
 * \return : 返回 gettimeofday 函数的值
 */
int My_gettimeofday(struct timeval *  tp,void *  tzp);
/*!
 * \brief My_gmtime : 包装了 gmtime 函数
 * \param calptr : 传递给 gmtime 函数的 calptr 参数
 * \return : 返回 gmtime 函数的值
 */
struct tm* My_gmtime(const time_t *calptr);
/*!
 * \brief My_localtime : 包装了 localtime 函数
 * \param calptr : 传递给 localtime 函数的 calptr 参数
 * \return : 返回 localtime 函数的值
 */
struct tm* My_localtime(const time_t *calptr);
/*!
 * \brief My_mktime : 包装了 mktime 函数
 * \param tmptr : 传递给 mktime 函数的 tmptr 参数
 * \return : 返回 mktime 函数的值
 */
time_t My_mktime(struct tm*tmptr);

/*!
 * \brief print_timespec ： 打印 timespec 时间
 * \param tm_tsp : struct timespec 时间
 */
void print_timespec(const struct timespec *tm_tsp);
/*!
 * \brief print_time_t ： 打印 time_t 时间
 * \param tmt : time_t 时间
 */
void print_time_t(const time_t tm_t);
/*!
 * \brief print_tm ： 打印 tm 时间
 * \param tm_tm : struct tm 时间
 */
void print_tm(const struct tm*tm_tm);
/*!
 * \brief print_timeval ： 打印 timeval 时间
 * \param tm_val: struct timeval 时间
 */
void print_timeval(const struct timeval *tm_val);
/*!
 * \brief test_times : 测试时间相关的函数
 */
void test_times();
#endif // TIMES_

