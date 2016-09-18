/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 getenv 函数、putenv 函数、setenv 函数、 unsetenv 函数，以及全局变量 environ 的用法。
 *
 */
#ifndef GETENV_SETENV
#define GETENV_SETENV

/*!
 * \brief My_getenv : 包装了 getenv 函数
 * \param name : 传递给 getenv  函数的  name 参数
 * \return : 返回了 getenv  函数的值
 */
char* My_getenv(const char*name);
/*!
 * \brief My_putenv : 包装了 putenv 函数
 * \param str : 传递给 putenv  函数的  str 参数
 * \return : 返回了 putenv  函数的值
 */
int My_putenv(char *str);
/*!
 * \brief My_setenv : 包装了 setenv 函数
 * \param name : 传递给  setenv 函数的  name 参数
 * \param value : 传递给  setenv 函数的  value 参数
 * \param rewrite : 传递给 setenv 函数的  rewrite 参数
 * \return : 返回了  setenv 函数的值
 */
int My_setenv(const char *name,const char *value,int rewrite);
/*!
 * \brief My_unsetenv : 包装了 unsetenv 函数
 * \param name : 传递给 unsetenv 函数的  name 参数
 * \return : 返回了 unsetenv 函数的值
 */
int My_unsetenv(const char *name);

/*!
 * \brief print_environ ： 打印全局的 envirion 变量
 */
void print_environ();
/*!
 * \brief test_getenv_setenv : 测试环境变量相关的函数
 */
void test_getenv_setenv();
#endif // GETENV_SETENV

