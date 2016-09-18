/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 * 这里是 dup 函数、dup2 函数的用法
 *
 */
#ifndef DUP_DUP2
#define DUP_DUP2

/*!
 * \brief My_dup : 包装了 dup  函数
 * \param fd : 传递给 dup 函数的 fd 参数
 * \return : 返回 dup 函数值
 */
int My_dup(int fd);
/*!
 * \brief My_dup2 : 包装了 dup2  函数
 * \param fd : 传递给 dup2 函数的 fd 参数
 * \param fd2 : 传递给 dup2 函数的 fd2 参数
 * \return : 返回 dup2 函数值
 */
int My_dup2(int fd,int fd2);
/*!
 * \brief test_dup_dup2 : 测试 dup、dup2 函数
 */
void test_dup_dup2();

#endif // DUP_DUP2

