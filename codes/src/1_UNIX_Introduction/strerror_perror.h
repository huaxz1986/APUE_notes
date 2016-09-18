/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第一章：UNIX 基础知识。
 *
 * 主要是 strerror 函数和 perror 函数的用法
 *
 */
#ifndef STRERROR_PERROR
#define STRERROR_PERROR

/*!
 * \brief test_strerror : 测试 strerror 函数的用法
 * \param errnum  :传递给 strerror 函数的 errnum 参数
 */
void test_strerror(int errnum);

/*!
 * \brief test_perror : 测试 perror 函数的用法
 * \param new_errno : 用它给全局的 errno 赋值
 * \param msg : 传递给 perror 函数的 msg 参数
 */
void test_perror(int new_errno,const char*msg);

/*!
 * \brief test_strerror_perror : 执行 strerror 的测试 和 perror 的测试
 */
void test_strerror_perror();
#endif // STRERROR_PERROR

