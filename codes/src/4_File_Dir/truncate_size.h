/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 truncate 函数的用法。 ftruncate 函数用法类似 truncate 函数用法
 *
 */
#ifndef TRUNCATE_SIZE
#define TRUNCATE_SIZE
#include<unistd.h>

/*!
 * \brief My_truncate : 包装了 truncate 函数
 * \param pathname : 传递给 truncate 函数的 pathname 参数
 * \param length : 传递给 truncate 函数的 length 参数
 * \return : 返回 truncate 函数的值
 */
int My_truncate(const char *pathname,off_t length);
/*!
 * \brief test_truncate_size : 测试 truncate 函数
 */
void test_truncate_size();

/*!
 * \brief truncate_and_read : 截断文件病读取文件内容
 * \param pathname : 文件名
 * \param fd: 文件描述符
 * \param length : 文件被劫断后的长度
 */
void truncate_and_read(const char *pathname,int fd,off_t length);
#endif // TRUNCATE_SIZE

