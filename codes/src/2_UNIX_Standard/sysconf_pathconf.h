/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第二章：UNIX 标准及实现。
 *
 * 主要是 sysconf 函数、pathconf函数的用法(fpathconf类似于 pathconf)
 *
 */
#ifndef SYSCONF_PATHCONF
#define SYSCONF_PATHCONF

/*!
 * \brief My_sysconf : sysconf 函数的包装函数
 * \param name : 传递给 sysconf 函数的 name 参数
 * \param name_str: name 参数对应的字符串，方便人员理解
 * \return : 返回 sysconf 函数的值
 */
long My_sysconf(int name,const char *name_str);

/*!
 * \brief My_pathconf : pathconf 函数的包装函数
 * \param pathname : 传递给 pathconf 函数的 pathname 参数
 * \param name : 传递给 pathconf 函数的 name 参数
 * \param name_str: name 参数对应的字符串，方便人员理解
 * \return : 返回 pathconf 函数的值
 */
long My_pathconf(const char*pathname,int name,const char *name_str);

/*!
 * \brief test_sycconf_pathconf : 执行 sysconf 的测试 和 pathconf 的测试
 */
void test_sycconf_pathconf();

#endif // SYSCONF_PATHCONF
