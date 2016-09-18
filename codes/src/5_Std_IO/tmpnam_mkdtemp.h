/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 tmpnam 函数、mkdtemp 函数的用法。
 * tmpfile 函数的用法类似 tmpnam 函数。
 * mkstemp 函数的用法类似 mkdtemp 函数。
 *
 *
 */
#ifndef TMPNAM_MKDTEMP
#define TMPNAM_MKDTEMP
#include<stdio.h>
#include<stdlib.h>

/*!
 * \brief My_tmpnam : 包装了 tmpnam  函数
 * \param ptr : 传递给 tmpnam 函数的 ptr 参数
 * \return : 返回 tmpnam 函数的值
 */
char *My_tmpnam(char *ptr);

/*!
 * \brief My_mkdtemp : 包装了 mkdtemp  函数
 * \param tmplate : 传递给 mkdtemp 函数的 template 参数
 * \return : 返回 mkdtemp 函数的值
 */
char *My_mkdtemp(char *tmplate);

/*!
 * \brief test_tmpnam_mkdtemp : 测试 tmpnam 函数和 mkdtemp  函数
 */
void test_tmpnam_mkdtemp();

/*!
 * \brief _test_tmpnam :测试 tmpnam 函数
 */
void _test_tmpnam();
/*!
 * \brief _test_mkdtemp :测试 mkdtemp 函数
 */
void _test_mkdtemp();
#endif // TMPNAM_MKDTEMP

