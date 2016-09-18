/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 getrlimit 函数、 setrlimit 函数的用法
 *
 */
#ifndef GETRLIMIT_SETRLIMIT
#define GETRLIMIT_SETRLIMIT
#include<sys/resource.h>

/*!
 * \brief My_getrlimit : 包装了 getrlimit 函数
 * \param resource : 传递给 getrlimit 函数的 rlptr 参数
 * \param rlptr : 传递给 getrlimit 函数的 rlptr 参数
 * \return  : 返回 getrlimit 函数的值
 */
int My_getrlimit(int resource,struct rlimit *rlptr);
/*!
 * \brief My_setrlimit : 包装了 setrlimit 函数
 * \param resource : 传递给 setrlimit 函数的 resource 参数
 * \param rlptr : 传递给 setrlimit 函数的 rlptr 参数
 * \return : 返回 setrlimit 函数的值
 */
int My_setrlimit(int resource,struct rlimit *rlptr);
/*!
 * \brief print_rlimit : 打印资源限制
 * \param rlptr : 指向 struct rlimit 的指针
 */
void print_rlimit(const struct rlimit *rlptr);
/*!
 * \brief test_getrlimit_setrlimit : 测试 getrlimit 函数、 setrlimit 函数
 */
void test_getrlimit_setrlimit();
#endif // GETRLIMIT_SETRLIMIT

