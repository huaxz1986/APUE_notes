/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 wait 函数、 waitpid 函数的用法
 *
 */
#ifndef WAIT_WAITPID
#define WAIT_WAITPID
#include<unistd.h>

/*!
 * \brief My_wait : 包装了 wait 函数
 * \param staloc : 传递给 wait 函数的 staloc 参数
 * \return : 返回 wait 函数的值
 */
pid_t My_wait(int *staloc);
/*!
 * \brief My_waitpid : 包装了 waitpid 函数
 * \param pid : 传递给 waitpid 函数的 pid 参数
 * \param staloc : 传递给 waitpid 函数的 staloc 参数
 * \param options : 传递给 waitpid 函数的 options 参数
 * \return : 返回 waitpid 函数的值
 */
pid_t My_waitpid(pid_t pid,int *staloc,int options);
/*!
 * \brief print_return_status : 打印进程终止状态码
 * \param staloc : 进程终止状态码
 */
void print_return_status(int staloc);

/*!
 * \brief check_wait : 使用 wait 等待所有子进程
 */
void check_wait();
/*!
 * \brief check_waitpid : 使用 waitpid 等待所有子进程
 */
void check_waitpid();
/*!
 * \brief check_waitpid_signal : 用于信号中断的 check_waitpid 函数
 *
 * 主要是进程在执行 `waitpid`调用而阻塞期间捕捉到一个信号，则该系统调用就会被中断而不再继续执行。
 * 此时`waitpid`返回出错，其`errno`设置为`EINTR`
 */
void check_waitpid_signal();

/*!
 * \brief child_exit : 创建一个子进程，其退出方式是 _exit
 * \param fd : 用于记录锁的文件描述符
 * \param exit_code : 子进程调用 _exit  的参数
 * \return : fork 的返回值
 */
pid_t child_exit(int fd,int exit_code);
/*!
 * \brief child_abort : 创建一个子进程，其退出方式是 abort
 * \param fd : 用于记录锁的文件描述符
 * \return  : fork 的返回值
 */
pid_t child_abort(int fd);
/*!
 * \brief child_signal : 创建一个子进程，其退出方式是信号终止
 * \param fd : 用于记录锁的文件描述符
 * \return  : fork 的返回值
 */
pid_t child_signal(int fd);

/*!
 * \brief test_wait_waitpid :测试 wait 函数、 waitpid 函数
 */
void test_wait_waitpid();
#endif // WAIT_WAITPID

