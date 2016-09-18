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

#include"sigprocmask_sigset.h"
#include"../header.h"
#include<signal.h>

int My_sigemptyset(sigset_t *set)
{
    int result=sigemptyset(set);
    if(-1==result)
    {
        printf("sigemptyset(%p) failed,because %s\n",
               set,strerror(errno));
    }
    else
    {
        printf("sigemptyset(%p) ok\n",set);
    }
    return result;
}
int My_sigfillset(sigset_t *set)
{
    int result=sigfillset(set);
    if(-1==result)
    {
        printf("sigfillset(%p) failed,because %s\n",
               set,strerror(errno));
    }
    else
    {
        printf("sigfillset(%p) ok\n",set);
    }
    return result;
}
int My_sigaddset(sigset_t *set,int signo)
{
    int result=sigaddset(set,signo);
    if(-1==result)
    {
        printf("sigaddset(%p,%d) failed,because %s\n",
               set,signo,strerror(errno));
    }
    else
    {
        printf("sigaddset(%p,%d) ok\n",set,signo);
    }
    return result;
}
int My_sigdelset(sigset_t *set,int signo)
{
    int result=sigdelset(set,signo);
    if(-1==result)
    {
        printf("sigdelset(%p,%d) failed,because %s\n",
               set,signo,strerror(errno));
    }
    else
    {
        printf("sigdelset(%p,%d) ok\n",set,signo);
    }
    return result;
}
int My_sigismember(const sigset_t *set,int signo)
{
    int result=sigismember(set,signo);
    if(1==result)
    {
        printf("sigismember(%p,%d):%d is in sigset %p\n",
               set,signo,signo,set);
    }else if(0==result)
    {
        printf("sigismember(%p,%d):%d is not in sigset %p\n",
                       set,signo,signo,set);
    }else
    {
        printf("sigismember(%p,%d) error,can not be here\n",
               set,signo);
    }
    return result;
}
int My_sigprocmask(int how,const sigset_t *set,sigset_t *oset)
{
    int result=sigprocmask(how,set,oset);
    if(-1==result)
    {
        printf("sigprocmask(%d,%p,%p) failed,because %s\n",
               how,set,oset,strerror(errno));
    }else
    {
        printf("sigprocmask(%d,%p,%p) ok\n",
               how,set,oset);
    }
    return result;
}

void print_sigset(const sigset_t *set)
{
    printf("sigset is :");
    if(NULL==set)
    {
        printf("NULL\n");
        return;
    }
    if(sigismember(set,SIGABRT)) printf("SIGABRT, ");
    if(sigismember(set,SIGALRM)) printf("SIGALRM, ");
    if(sigismember(set,SIGBUS)) printf("SIGBUS, ");
    if(sigismember(set,SIGCHLD)) printf("SIGCHLD, ");
    if(sigismember(set,SIGCONT)) printf("SIGCONT, ");
    if(sigismember(set,SIGFPE)) printf("SIGFPE, ");
    if(sigismember(set,SIGHUP)) printf("SIGHUP, ");
    if(sigismember(set,SIGILL)) printf("SIGILL, ");
    if(sigismember(set,SIGINT)) printf("SIGINT, ");
    if(sigismember(set,SIGIO)) printf("SIGIO, ");
    if(sigismember(set,SIGIOT)) printf("SIGIOT, ");
    if(sigismember(set,SIGKILL)) printf("SIGKILL, ");
    if(sigismember(set,SIGPIPE)) printf("SIGPIPE, ");
    if(sigismember(set,SIGPOLL)) printf("SIGPOLL, ");
    if(sigismember(set,SIGPROF)) printf("SIGPROF, ");
    if(sigismember(set,SIGPWR)) printf("SIGPWR, ");
    if(sigismember(set,SIGQUIT)) printf("SIGQUIT, ");
    if(sigismember(set,SIGSEGV)) printf("SIGSEGV, ");
    if(sigismember(set,SIGSTKFLT)) printf("SIGSTKFLT, ");
    if(sigismember(set,SIGSTOP)) printf("SIGSTOP, ");
    if(sigismember(set,SIGSYS)) printf("SIGSYS, ");
    if(sigismember(set,SIGTERM)) printf("SIGTERM, ");
    if(sigismember(set,SIGTRAP)) printf("SIGTRAP, ");
    if(sigismember(set,SIGTSTP)) printf("SIGTSTP, ");
    if(sigismember(set,SIGTTIN)) printf("SIGTTIN, ");
    if(sigismember(set,SIGTTOU)) printf("SIGTTOU, ");
    if(sigismember(set,SIGURG)) printf("SIGURG, ");
    if(sigismember(set,SIGUSR1)) printf("SIGUSR1, ");
    if(sigismember(set,SIGUSR2)) printf("SIGUSR2, ");
    if(sigismember(set,SIGVTALRM)) printf("SIGVTALRM, ");
    if(sigismember(set,SIGWINCH)) printf("SIGWINCH, ");
    if(sigismember(set,SIGXCPU)) printf("SIGXCPU, ");
    if(sigismember(set,SIGXFSZ)) printf("SIGXFSZ, ");
    printf("\n");
}
void print_progress_mask_sigset()
{
    sigset_t old_set;
    if(-1==sigprocmask(SIG_SETMASK,NULL,&old_set)) // 当 set 为 NULL 时， how 参数没有意义
    {
        printf("print_progress_mask_sigset error,because %s\n",strerror(errno));
    }else
    {
        printf("process current mask sigset is:");
        print_sigset(&old_set);
    }
}


void test_sigprocmask_sigset()
{
    M_TRACE("---------  Begin test_sigprocmask_sigset()  ---------\n");
    sigset_t set;
    //********** 测试操作 sigset **********//
    printf("********** sigset operation ***********\n");
    My_sigemptyset(&set);
    print_sigset(&set); // 打印信号集
    My_sigaddset(&set,SIGINT);
    print_sigset(&set); // 打印信号集
    My_sigfillset(&set);
    print_sigset(&set); // 打印信号集
    My_sigdelset(&set,SIGINT);
    print_sigset(&set); // 打印信号集
    My_sigismember(&set,SIGINT);
    My_sigismember(&set,SIGCHLD);
    //********** 测试 sigprocmask **********//
    sigset_t o_set;
    printf("\n\n********** sigprocmask operation ***********\n");
    print_progress_mask_sigset();// 打印进程的信号屏蔽字
    My_sigprocmask(SIG_BLOCK,&set,&o_set);
    print_progress_mask_sigset();// 打印进程的信号屏蔽字
    My_sigprocmask(SIG_UNBLOCK,&set,NULL);
    print_progress_mask_sigset();// 打印进程的信号屏蔽字
    My_sigprocmask(SIG_SETMASK,&set,NULL);
    print_progress_mask_sigset();// 打印进程的信号屏蔽字
    My_sigprocmask(SIG_SETMASK,&o_set,NULL); // 还原信号屏蔽字
    M_TRACE("---------  End test_sigprocmask_sigset()  ---------\n\n");
}
