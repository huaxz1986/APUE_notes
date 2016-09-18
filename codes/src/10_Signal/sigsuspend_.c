/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigsuspend 函数的用法
 *
 */
#include"sigsuspend_.h"
#include"../header.h"
typedef void Hanlder_Func (int signo,siginfo_t *info, void *context);
extern void print_sigset(const sigset_t *set);
extern void print_progress_pending_sigset();
extern void print_progress_mask_sigset();
extern void add_sigaction(int signo,sigset_t *set,int no_deffer,int restart,Hanlder_Func handler);
extern int My_sigemptyset(sigset_t *set);
extern int My_sigaddset(sigset_t *set,int signo);
extern int My_sigprocmask(int how,const sigset_t *set,sigset_t *oset);
extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid_signal();

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
    print_progress_mask_sigset(); // 当前进程的信号屏蔽字
    print_progress_pending_sigset(); // 当前进程的未决的信号集
    printf("------ End signal Hanlder<signo=%s> ------\n\n",strsignal(signo));
}
/*!
 * \brief create_child : 创建子进程
 * \return : fork 的返回值
 */
static pid_t create_child()
{
    pid_t pid=fork();
    if(0==pid)
    {// child
        printf("************ In Child **********\n");
        sleep(2);//让父进程先到达 sigsuspend
        print_pid();
        print_parent_pid();
        My_kill(getppid(),SIGINT); // 向父进程发送信号
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}
int My_sigsuspend(const sigset_t *sigmask)
{
    int result=sigsuspend(sigmask);
    printf("return from sigsuspend,return %d,errno is %s\n"
           ,result,strerror(errno));
    return result;
}

void test_sigsuspend()
{
    M_TRACE("---------  Begin test_sigsuspend()  ---------\n");
    //***** 添加信号处理程序 ****//
    add_sigaction(SIGINT,NULL,0,1,sig_print);
    add_sigaction(SIGALRM,NULL,0,1,sig_print);
    create_child();
    //***** 只有父进程能到达此处 ******//

    print_progress_mask_sigset(); // 当前进程的信号屏蔽字
    print_progress_pending_sigset(); // 当前进程的未决的信号集
    sigset_t set;
    My_sigemptyset(&set);
    My_sigaddset(&set,SIGINT);
    My_sigsuspend(&set); //投入睡眠
    print_progress_mask_sigset(); // 当前进程的信号屏蔽字
    print_progress_pending_sigset(); // 当前进程的未决的信号集
    check_waitpid_signal();

    M_TRACE("---------  End test_sigsuspend()  ---------\n\n");
}
