/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 getpid 函数、 getppid 函数... 等进程 ID 相关函数的用法
 *
 */
#ifndef PROGRESS_ID
#define PROGRESS_ID

/*!
 * \brief print_pid : 打印进程 id
 */
void print_pid();
/*!
 * \brief print_parent_pid : 打印进程的父进程 id
 */
void print_parent_pid();
/*!
 * \brief print_uid  : 打印进程的用户 id
 */
void print_uid();
/*!
 * \brief print_euid : 打印进程的有效用户 id
 */
void print_euid();
/*!
 * \brief print_gid : 打印进程的组 id
 */
void print_gid();
/*!
 * \brief print_egid : 打印进程的有效组 id
 */
void print_egid();
/*!
 * \brief test_progress_id : 测试 getpid 函数、 getppid 函数... 等进程 ID 相关函数
 */
void test_progress_id();
#endif // PROGRESS_ID

