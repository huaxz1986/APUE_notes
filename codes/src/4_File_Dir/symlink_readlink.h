/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 symlink 函数和 readlink 函数的用法。 symlinkat 函数用法类似 symlink 函数用法。
 * readlinkat 函数用法类似 readlink 函数用法。
 *
 */
#ifndef SYMLINK_READLINK
#define SYMLINK_READLINK
#include<sys/types.h>

/*!
 * \brief My_symlink : 包装了 symlink 函数
 * \param actualpath : 传递给 symlink 函数的 actualpath 参数
 * \param sympath : 传递给 symlink 函数的 sympath 参数
 * \return : 返回 symlink 函数的值
 */
int My_symlink(const char*actualpath,const char *sympath);
/*!
 * \brief My_readlink : 包装了 readlink 函数
 * \param pathname : 传递给 readlink 函数的 pathname 参数
 * \param buf :  传递给 readlink 函数的 buf 参数
 * \param bufsize :  传递给 readlink 函数的 bufsize 参数
 * \return : 返回 readlink 函数的值
 */
ssize_t My_readlink(const char * pathname,char * buf,size_t bufsize);
/*!
 * \brief print_link_file : 打印链接文件的内容
 * \param pathname : 链接文件名
 */
void print_link_file(const char * pathname);

/*!
 * \brief test_symlink_readlink : 测试 symlink 函数、 readlink 函数
 */
void test_symlink_readlink();

#endif // SYMLINK_READLINK

