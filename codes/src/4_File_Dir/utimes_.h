/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 utimes 函数的用法。 utimensat 函数、 futimens 函数用法类似 utimes 函数用法
 *
 */
#ifndef UTIMES_
#define UTIMES_
#include<sys/time.h>




/*!
 * \brief My_utimes :  包装了 utimes 函数
 * \param pathname : 传递给 utimes 函数的 pathname 参数
 * \param times : 传递给 utimes 函数的 times 参数
 * \return : 返回 utimes 函数的值
 */
int My_utimes(const char*pathname,const struct timeval times[2]);

/*!
 * \brief test_utimes : 测试 utimes 函数
 */
void test_utimes();
#endif // UTIMES_

