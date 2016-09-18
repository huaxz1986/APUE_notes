/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 kill 函数、raise 函数的用法
 *
 */

#include"kill_raise.h"
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

extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid_signal();


int My_kill(pid_t pid, int signo)
{
    int result=kill(pid,signo);
    if(-1==result)
    {
        printf("kill(%d,%d) failed,because %s\n",
               pid,signo,strerror(errno));
    }else
    {
        printf("kill(%d,%d) ok\n",pid,signo);
    }
    return result;
}
int My_raise(int signo)
{
    int result=raise(signo);
    if(-1==result)
    {
        printf("raise(%d) failed,because %s\n",
               signo,strerror(errno));
    }else
    {
        printf("raise(%d) ok\n",signo);
    }
    return result;
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
        print_pid();
        print_parent_pid();
        My_kill(1,SIGINT); // 向 init 进程发送信号
        My_kill(1,0); // 向 init 进程发送信号
        My_kill(getppid(),0); // 向父进程发送信号
        My_kill(0,SIGINT); // 向进程组发送信号
        My_raise(SIGINT); // 给自己发送信号
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}

void test_kill_raise()
{
    M_TRACE("---------  Begin test_kill_raise()  ---------\n");
    add_sigaction(SIGCHLD,NULL,0,0,sig_print);
    add_sigaction(SIGINT,NULL,0,0,sig_print);
    create_child();
    // 只有父进程能到达此处
    check_waitpid_signal();
    print_pid();
    print_parent_pid();
    M_TRACE("---------  End test_kill_raise()  ---------\n\n");
}
