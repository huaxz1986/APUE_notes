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
#include"sigaction_.h"
#include"../header.h"
#include<unistd.h>

extern void print_sigset(const sigset_t *set);
extern void print_progress_pending_sigset();
extern void print_progress_mask_sigset();
extern int My_sigemptyset(sigset_t *set);
extern int My_sigaddset(sigset_t *set,int signo);
extern int My_sigprocmask(int how,const sigset_t *set,sigset_t *oset);
extern void check_waitpid();

int My_sigaction(int signo, const struct sigaction *act, struct sigaction *oact)
{
    int result=sigaction(signo,act,oact);
    if(-1==result)
    {
        printf("sigaction(%d,%p,%p) failed,because %s\n",
               signo,act,oact,strerror(errno));
    }else
    {
        printf("sigaction(%d,%p,%p) ok\n",
               signo,act,oact);
    }
    return result;
}

void print_siginfo_t(const siginfo_t *info)
{
    printf("siginfo_t:");
    if(NULL==info)
    {
        printf("NULL\n");
        return;
    }
    printf("si_signo:%d\n",info->si_signo);
    printf("si_errno:%d(%s)\n",info->si_errno,strerror(info->si_errno));
    printf("si_code:%d\n",info->si_code);
}
void print_context_t(const ucontext_t *t)
{
    printf("context_t:");
    if(NULL==t)
    {
        printf("NULL\n");
        return;
    }
    printf("uc_link:%p\n",t->uc_link);
    printf("uc_sigmask:");
    print_sigset(&t->uc_link);
    printf("uc_stack->ss_sp:%p\n",t->uc_stack.ss_sp);
    printf("uc_stack->ss_size:%d\n",t->uc_stack.ss_size);
}
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
    print_context_t((ucontext_t *)context);
    print_progress_mask_sigset(); // 打印进程当前的信号屏蔽字
    print_progress_pending_sigset(); // 打印进程当前的未决的信号集
    printf("------ End signal Hanlder<signo=%s> ------\n\n",strsignal(signo));
}

void add_sigaction(int signo,sigset_t *set,int no_deffer,int restart,Hanlder_Func handler)
{
    sigset_t empty_set;
    sigemptyset(&empty_set);

    struct sigaction action;
    action.sa_sigaction=handler;

    action.sa_flags=SA_SIGINFO;
    if(no_deffer!=0) //捕捉到信号时，在执行信号处理函数时，不自动阻塞该信号
        action.sa_flags|=SA_NODEFER;
    if(0==restart) // 由此信号中断的系统调用并不会自动重启
        action.sa_flags|=SA_INTERRUPT;
    else // 由此信号中断的系统调用会自动重启
        action.sa_flags|=SA_RESTART;

    if(NULL==set)
        action.sa_mask=empty_set;
    else
        action.sa_mask=*set;
    My_sigaction(signo,&action,NULL);
}
void test_sigaction()
{
    M_TRACE("---------  Begin test_sigaction()  ---------\n");
    print_progress_mask_sigset();

    //********* 设置进程的信号屏蔽字 *****//
    sigset_t set;
    My_sigemptyset(&set);
    My_sigaddset(&set,SIGPIPE);
    My_sigprocmask(SIG_SETMASK,&set,NULL);
    print_progress_mask_sigset();

    //******** 添加信号处理程序 ********//
    add_sigaction(SIGINT,NULL,1,1,sig_print); // 几种组合：是否 no_deffer，是否 restart

    if(fork()==0)
    {
        sleep(1); // 子进程先睡眠，使得父进程进入 check_waitpid()
        kill(getppid(),SIGINT); // 子进程发送 SIGINT 到父进程
        sleep(10); //子进程不是马上结束
        _exit(0);
    }
    check_waitpid();
    print_progress_mask_sigset();

    M_TRACE("---------  End test_sigaction()  ---------\n\n");
}


