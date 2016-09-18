/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 setjmp 函数、 longjmp 函数的用法
 *
 */
#ifndef SETJMP_LONGJMP
#define SETJMP_LONGJMP
#include<setjmp.h>
/*!
 * \brief print_jmp_buf : 打印 jmp_buf 对象
 * \param env : 待打印的 jmp_buf 对象
 */
void print_jmp_buf(const jmp_buf env);
/*!
 * \brief test_setjmp_longjmp :测试 setjmp 函数、 longjmp 函数的用法
 */
void test_setjmp_longjmp();
#endif // SETJMP_LONGJMP

