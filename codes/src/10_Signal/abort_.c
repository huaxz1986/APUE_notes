/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 abort 函数的用法
 *
 */

#include"abort_.h"
#include"../header.h"
#include<signal.h>
typedef void Hanlder_Func (int signo,siginfo_t *info, void *context);
extern void print_progress_mask_sigset();
extern int My_sigemptyset(sigset_t *set);
extern int My_sigaddset(sigset_t *set,int signo);
extern void print_progress_mask_sigset();
extern int My_sigprocmask(int how,const sigset_t *set,sigset_t *oset);
extern void add_sigaction(int signo,sigset_t *set,int no_deffer,int restart,Hanlder_Func handler);
/*!
 * \brief sig_print : 信号处理函数
 * \param signo : 信号值
 * \param info : 指向 siginfo_t 的指针
 * \param context : 指向 ucontext_t * 的指针
 */
static void sig_print(int signo,siginfo_t *info, void *context)
{
    printf("------ Begin signal Hanlder<signo=%s> ------\n",strsignal(signo));
    psiginfo(info,"The siginfo is:\t");
    printf("------ End signal Hanlder<signo=%s> ------\n\n",strsignal(signo));
}

void test_abort()
{
    M_TRACE("---------  Begin test_abort()  ---------\n");

    //**** 添加信号处理程序 ****//
    add_sigaction(SIGABRT,NULL,0,1,sig_print);
    //**** 设置进程的信号屏蔽字  ****//
    print_progress_mask_sigset(); // 打印进程的信号屏蔽字
    sigset_t set;
    sigset_t o_set; // 保存旧的进程的信号屏蔽字
    My_sigemptyset(&set);
    My_sigaddset(&set,SIGABRT);
    My_sigprocmask(SIG_SETMASK,&set,&o_set);//设置进程的信号屏蔽字
    print_progress_mask_sigset(); // 打印进程的信号屏蔽字

    //*****  调用 abort() ****//
    abort();

    My_sigprocmask(SIG_SETMASK,&o_set,NULL); // 恢复进程的信号屏蔽字
    M_TRACE("---------  End test_abort()  ---------\n\n");
}
