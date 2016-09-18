/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 malloc 函数、 calloc 函数、realloc 函数的用法。
 *
 */
#ifndef MALLOC_REALLOC
#define MALLOC_REALLOC
#include<stdlib.h>

/*!
 * \brief My_malloc : 包装了 malloc 函数
 * \param size : 传递给 malloc 函数的 size 参数
 * \return : 返回 malloc 函数的值
 */
void* My_malloc(size_t size);
/*!
 * \brief My_calloc : 包装了 calloc 函数
 * \param nobj : 传递给 calloc 函数的 nobj 参数
 * \param size : 传递给 calloc 函数的 size 参数
 * \return  : 返回 calloc 函数的值
 */
void* My_calloc(size_t nobj,size_t size);
/*!
 * \brief My_realloc : 包装了 realloc 函数
 * \param ptr : 传递给 realloc 函数的 ptr 参数
 * \param newsize : 传递给 realloc 函数的 newsize 参数
 * \return  : 返回 realloc 函数的值
 */
void* My_realloc(void *ptr,size_t newsize);

void test_malloc_realloc();

#endif // MALLOC_REALLOC

