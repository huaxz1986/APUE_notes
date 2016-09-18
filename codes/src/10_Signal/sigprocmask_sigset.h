/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigprocmask 函数、sigemptyset 函数、sigfillset 函数、sigaddset 函数、
 *  sigdelset 函数、 sigismember 函数的用法
 *
 */
#ifndef SIGPROCMASK_SIGSET
#define SIGPROCMASK_SIGSET

#include<signal.h>

/*!
 * \brief My_sigemptyset : 包装了 sigemptyset 函数
 * \param set : 传递给 sigemptyset 函数的 set 参数
 * \return : 返回 sigemptyset 函数的值
 */
int My_sigemptyset(sigset_t *set);
/*!
 * \brief My_sigfillset : 包装了 sigfillset 函数
 * \param set : 传递给 sigfillset 函数的 set 参数
 * \return : 返回 sigfillset 函数的值
 */
int My_sigfillset(sigset_t *set);
/*!
 * \brief My_sigaddset : 包装了 sigaddset 函数
 * \param set : 传递给 sigaddset 函数的 set 参数
 * \param signo : 传递给 sigaddset 函数的 signo 参数
 * \return : 返回 sigaddset 函数的值
 */
int My_sigaddset(sigset_t *set,int signo);
/*!
 * \brief My_sigdelset : 包装了sigdelset  函数
 * \param set : 传递给 sigdelset 函数的 set 参数
 * \param signo : 传递给 sigdelset 函数的 signo 参数
 * \return : 返回 sigdelset 函数的值
 */
int My_sigdelset(sigset_t *set,int signo);
/*!
 * \brief My_sigismember : 包装了 sigismember 函数
 * \param set : 传递给 sigismember 函数的 set 参数
 * \param signo : 传递给 sigismember 函数的 signo 参数
 * \return : 返回 sigismember 函数的值
 */
int My_sigismember(const sigset_t *set,int signo);
/*!
 * \brief My_sigprocmask : 包装了 sigprocmask 函数
 * \param how : 传递给 sigprocmask 函数的 how 参数
 * \param set : 传递给 sigprocmask 函数的 set 参数
 * \param oset : 传递给 sigprocmask 函数的 oset 参数
 * \return : 返回 sigprocmask 函数的值
 */
int My_sigprocmask(int how,const sigset_t *set,sigset_t *oset);

/*!
 * \brief print_sigset : 打印信号集
 * \param set : 指向信号集的指针
 */
void print_sigset(const sigset_t *set);
/*!
 * \brief print_progress_mask_sigset : 打印进程当前的信号屏蔽字
 */
void print_progress_mask_sigset();
/*!
 * \brief test_sigprocmask_sigset : 测试 sigprocmask 函数以及 sigset 操作函数
 */
void test_sigprocmask_sigset();
#endif // SIGPROCMASK_SIGSET

