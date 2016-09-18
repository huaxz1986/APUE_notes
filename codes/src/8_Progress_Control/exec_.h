/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 exec 函数族的用法
 *
 */
#ifndef EXEC_
#define EXEC_

/*!
 * \brief _test_execl ：测试 execl 函数的用法
 * \param pathname : 可执行文件的路径名
 */
void _test_execl(const char* pathname);
/*!
 * \brief _test_execv ：测试 execv 函数的用法
 * \param pathname : 可执行文件的路径名
 */
void _test_execv(const char* pathname);
/*!
 * \brief _test_execle ：测试 execle 函数的用法
 * \param pathname : 可执行文件的路径名
 */
void _test_execle(const char* pathname);
/*!
 * \brief _test_execve ：测试 execve 函数的用法
 * \param pathname : 可执行文件的路径名
 */
void _test_execve(const char* pathname);
/*!
 * \brief _test_execlp ：测试 execlp 函数的用法
 * \param pathname : 可执行文件的文件名
 */
void _test_execlp(const char* filename);
/*!
 * \brief _test_execvp ：测试 execvp 函数的用法
 * \param pathname : 可执行文件的文件名
 */
void _test_execvp(const char* filename);

/*!
 * \brief test_exec :测试 exec 函数族的用法
 */
void test_exec();

#endif // EXEC_

