/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigsetjmp 函数、 siglongjmp 函数的用法
 *
 */
#ifndef SIGSETJMP_SIGLONGJMP
#define SIGSETJMP_SIGLONGJMP
#include<setjmp.h>

/*!
 * \brief print_sigjmp_buf : 打印 sigjmp_buf 对象
 * \param env : 待打印的 sigjmp_buf 对象
 */
void print_sigjmp_buf(const sigjmp_buf env);
/*!
 * \brief test_sigsetjmp_siglongjmp :测试 sigsetjmp 函数、 siglongjmp 函数的用法
 */
void test_sigsetjmp_siglongjmp();
#endif // SIGSETJMP_SIGLONGJMP

