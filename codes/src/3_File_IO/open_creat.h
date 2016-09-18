/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 * 这里是 open 和 creat 函数的用法。 openat 用法类似 open
 *
 */
#ifndef OPEN_CREATE
#define OPEN_CREATE
#include<fcntl.h>
/*!
 * \brief My_open : 包装了 open 函数（不带 mode参数）
 * \param path : 传递给 open 函数的 path 参数
 * \param oflag : 传递给 open 函数的 oflag 参数
 * \return : 返回 open 函数的值
 */
int My_open(const char*path,int oflag);

/*!
 * \brief My_open_with_mode : 包装了 open 函数（带 mode参数）
 * \param path : 传递给 open 函数的 path 参数
 * \param oflag : 传递给 open 函数的 oflag 参数
 * \param mode : 传递给 open 函数的 mode 参数
 * \return : 返回 open 函数的值
 */
int My_open_with_mode(const char*path,int oflag,mode_t mode);

/*!
 * \brief My_creat : 包装了 creat 函数
 * \param path : 传递给 creat 函数的 path 参数
 * \param mode : 传递给 creat 函数的 mode 参数
 * \return : 返回 creat 函数的值
 */
int My_creat(const char*path,mode_t mode);


/*!
 * \brief test_open_creat: 执行 open 的测试 和 creat 的测试
 */
void test_open_creat();


#endif // OPEN_CREATE

