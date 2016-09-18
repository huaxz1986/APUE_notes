/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 access 函数和 umask 函数的用法。 faccess 函数用法类似 access 函数用法
 *
 */
#ifndef ACCESS_UMASK
#define ACCESS_UMASK
#include<sys/stat.h>

/*!
 * \brief My_access : 包装了 access 函数
 * \param pathname : 传递给 access 函数的 pathname 参数
 * \param mode : 传递给 access 函数的 mode  参数
 * \return : 返回 access 函数的值
 */
int My_access(const char *pathname,int mode);
/*!
 * \brief My_umask : 包装了 umask 函数
 * \param cmask : 传递给 umask 函数的 cmask  参数
 * \return : 返回 umask 函数的值
 */
mode_t My_umask(mode_t cmask);
/*!
 * \brief test_access_umask : 测试 access 函数、 umask 函数
 */
void test_access_umask();

#endif // ACCESS_UMASK

