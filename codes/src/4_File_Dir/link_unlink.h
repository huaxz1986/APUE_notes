/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 link 函数和 unlink 函数的用法。 linkat 函数用法类似 link 函数用法
 * unlinkat 函数用法类似 unlink 函数用法
 *
 */
#ifndef LINK_UNLINK
#define LINK_UNLINK
/*!
 * \brief My_link : 包装了 link 函数
 * \param existingpath : 传递给 link 函数的 existingpath 参数
 * \param newpath  : 传递给 link 函数的 newpath 参数
 * \return : 返回 link 函数的值
 */
int My_link(const char *existingpath,const char *newpath);
/*!
 * \brief My_unlink : 包装了 unlink 函数
 * \param pathname : 传递给 unlink 函数的 pathname 参数
 * \return : 返回 unlink 函数的值
 */
int My_unlink(const char*pathname);
/*!
 * \brief test_link_unlink ：测试 link 函数、 unlink 函数
 */
void test_link_unlink();
#endif // LINK_UNLINK

