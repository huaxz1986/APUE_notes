/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 nice 函数、 getpriority 函数、 setpriority 函数的用法
 *
 */
#ifndef GETPRIORITY_SETPRIORITY
#define GETPRIORITY_SETPRIORITY
#include<sys/resource.h>

/*!
 * \brief My_nice : 包装了 nice 函数
 * \param incr : 传递给 nice 函数的 incr 参数
 * \return : 返回 nice 函数的值
 */
int My_nice(int incr);
/*!
 * \brief My_getpriority : 包装了 getpriority 函数
 * \param which : 传递给 getpriority 函数的 which 参数
 * \param who : 传递给 getpriority 函数的 who 参数
 * \return : 返回 getpriority 函数的值
 */
int My_getpriority(int which,id_t who);
/*!
 * \brief My_setpriority : 包装了 setpriority 函数
 * \param which : 传递给 setpriority 函数的 which 参数
 * \param who : 传递给 setpriority 函数的 who 参数
 * \param value : 传递给 setpriority 函数的 value 参数
 * \return : 返回 setpriority 函数的值
 */
int My_setpriority(int which,id_t who,int value);

/*!
 * \brief test_getpriority_setpriority:测试 nice 函数、 getpriority 函数、 setpriority 函数
 */
void test_getpriority_setpriority();
#endif // GETPRIORITY_SETPRIORITY

