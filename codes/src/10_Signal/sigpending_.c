/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigpending 函数的用法
 *
 */
#include"sigpending_.h"
#include"../header.h"
#include<signal.h>
typedef void Hanlder_Func (int signo,siginfo_t *info, void *context);
extern void add_sigaction(int signo,sigset_t *set,int no_deffer,int restart,Hanlder_Func handler);
/*!
 * \brief sig_print : 信号处理函数
 * \param signo : 信号值
 * \param info : 指向 siginfo_t 的指针
 * \param context : 指向 ucontext_t * 的指针
 */
static void sig_print(int signo,siginfo_t *info, void *context)
{
    printf("------ Begin signal Hanlder<signo=%s> ------\n\n",strsignal(signo));
    psiginfo(info,"The siginfo is:\t");
    printf("------ End signal Hanlder<signo=%s> ------\n\n",strsignal(signo));
}

extern void print_sigset(sigset_t *set);
extern void print_progress_mask_sigset();
extern int My_sigemptyset(sigset_t *set);
extern int My_sigaddset(sigset_t *set,int signo);
extern void print_progress_mask_sigset();
extern int My_sigprocmask(int how,const sigset_t *set,sigset_t *oset);

int My_sigpending(sigset_t *set)
{
    int result=sigpending(set);
    if(-1==result)
    {
        printf("sigpending(%p) error,because %s\n",
               set,strerror(errno));
    }
    else
    {
        printf("sigpending(%p) ok,the pending signal is:",set);
        print_sigset(set);
    }
    return result;
}
void print_progress_pending_sigset()
{
    sigset_t pending_set;
    My_sigpending(&pending_set); // 查看未决的信号集
}

void test_sigpending()
{
    M_TRACE("---------  Begin test_sigpending()  ---------\n");

    //添加信号处理程序
    add_sigaction(SIGINT,NULL,0,0,sig_print);
    add_sigaction(SIGALRM,NULL,0,0,sig_print);
    add_sigaction(SIGCONT,NULL,0,0,sig_print);
    //**** 设置进程的信号屏蔽字 *****//
    sigset_t set,o_set;
    My_sigemptyset(&set);
    My_sigaddset(&set,SIGINT);
    My_sigaddset(&set,SIGALRM);
    print_progress_mask_sigset(); // 打印原始的信号屏蔽字
    My_sigprocmask(SIG_SETMASK,&set,&o_set);// 设置新的信号屏蔽字
    print_progress_mask_sigset(); // 打印新的信号屏蔽字

    //******* 查看未决的信号 *****//
    print_progress_pending_sigset();
    raise(SIGCONT);
    raise(SIGINT);
    raise(SIGALRM);
    print_progress_pending_sigset(); // 发送三个信号之后，未决的信号集
    //***** 设置进程的信号屏蔽字为空 *****//
    My_sigemptyset(&set);
    My_sigprocmask(SIG_SETMASK,&set,NULL);// 设置新的信号屏蔽字
    print_progress_mask_sigset(); // 打印新的信号屏蔽字
    print_progress_pending_sigset(); // 查看未决的信号集

    My_sigprocmask(SIG_SETMASK,&o_set,NULL);// 还原信号屏蔽字
    M_TRACE("---------  End test_sigpending()  ---------\n\n");
}
