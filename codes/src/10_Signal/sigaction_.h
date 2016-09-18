/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigaction 函数的用法
 *
 */
#ifndef SIGACTION_
#define SIGACTION_
#include"../header.h"
#include<signal.h>

typedef void Hanlder_Func (int signo,siginfo_t *info, void *context);
/*!
 * \brief My_sigaction : 包装了 sigaction 函数
 * \param signo : 传递了  sigaction 函数的 signo 参数
 * \param act : 传递了 sigaction  函数的 act 参数
 * \param oact : 传递了  sigaction 函数的 oact 参数
 * \return : 返回 sigaction 函数的值
 */
int My_sigaction(int signo,const struct sigaction *act
            ,struct sigaction*oact);


/*!
 * \brief print_context_t : 打印 ucontext_t 内容
 * \param t : 指向 ucontext_t 的指针
 */
void print_context_t(const ucontext_t *t);
/*!
 * \brief print_siginfo_t : 打印 siginfo_t 内容
 * \param info : 指向 siginfo_t 的指针
 */
void print_siginfo_t(const siginfo_t *info);

/*!
 * \brief add_sigaction : 添加信号处理函数
 * \param signo : 信号值
 * \param set : 指向 sigset_t 的指针
 * \param no_deffer : 非 0 则表示在执行其信号处理函数时，系统并不自动阻塞此信号
 * \param restart : 为 0 表示不自动重启中断的系统调用；非0表示自动重启被中断的系统
 * \param handler : 信号处理函数
 */
void add_sigaction(int signo,sigset_t *set,int no_deffer,int restart,Hanlder_Func handler);

/*!
 * \brief test_sigaction :测试 sigaction 函数的用法
 */
void test_sigaction();
#endif // SIGACTION_

