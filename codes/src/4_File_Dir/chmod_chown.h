/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 chmod 函数和 chown 函数的用法。 fchown 函数、 fchown函数、  lchown用法类似 chown 函数用法。
 * fchmod 函数、 fchmodat 函数用法类似 chmod 函数。
 *
 */
#ifndef CHMOD_CHOWN
#define CHMOD_CHOWN
#include "stat_lstat.h"

/*!
 * \brief My_chmod : 包装了 chmod 函数
 * \param pathname : 传递给 chmod 函数的 pathname 参数
 * \param mode : 传递给 chmod 函数的 pathname 参数
 * \return : 返回 chmod 函数的值
 */
int My_chmod(const char*pathname,mode_t mode);
/*!
 * \brief My_chown : 包装了 chown 函数
 * \param pathname : 传递给 chown 函数的 pathname 参数
 * \param owner : 传递给 chown 函数的 owner 参数
 * \param group : 传递给 chown 函数的 group 参数
 * \return : 返回 chown 函数的值
 */
int My_chown(const char *pathname,uid_t owner,gid_t group);
/*!
 * \brief test_chmod_chown : 测试 chmod 函数和 chown 函数
 */
void test_chmod_chown();


#endif // CHMOD_CHOWN

