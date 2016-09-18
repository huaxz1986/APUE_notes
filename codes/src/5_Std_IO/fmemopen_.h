/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 fmemopen 函数的用法。
 * open_memstream 函数、 open_wmemstream 函数的用法类似 fmemopen 函数。
 *
 */
#ifndef FMEMOPEN_
#define FMEMOPEN_
#include<stdio.h>
/*!
 * \brief My_fmemopen : 包装了 fmemopen 函数
 * \param buf : 传递给 fmemopen 函数的 buf 参数
 * \param size : 传递给 fmemopen 函数的 size 参数
 * \param type : 传递给 fmemopen 函数的 type 参数
 * \return : 返回 fmemopen函数的值
 */
FILE *My_fmemopen(void *buf,size_t size,const char *type);

/*!
 * \brief test_memstream : 测试内存流的使用
 */
void test_memstream();
#endif // FMEMOPEN_

