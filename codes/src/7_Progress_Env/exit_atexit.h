/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 exit 函数、 _Exit 函数、 _exit 函数的用法
 *
 */
#ifndef EXIT_ATEXIT
#define EXIT_ATEXIT

/*!
 * \brief add_atexit : 添加终止处理程序 exit handler
 */
void add_atexit();
/*!
 * \brief test_exit_atexit : 测试 exit 函数、 _Exit 函数、 _exit 函数
 */
void test_exit_atexit();
#endif // EXIT_ATEXIT

