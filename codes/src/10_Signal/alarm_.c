/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 alarm 函数的用法
 *
 */
#include"alarm_.h"
#include"../header.h"
#include<unistd.h>
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


unsigned int My_alarm(unsigned int seconds)
{
    unsigned int result=alarm(seconds);
    printf("alarm(%d) returns %d\n",seconds,result);
    return result;
}
void test_alarm()
{
    M_TRACE("---------  Begin test_alarm()  ---------\n");
    add_sigaction(SIGALRM,NULL,0,0,sig_print);
    My_alarm(2) ; // 2s 定时器
    sleep(3);
    My_alarm(3); //3s 定时器
    sleep(1);
    My_alarm(0);// 取消定时器
    sleep(3);
    My_alarm(4); //4s 定时器
    My_alarm(2); //2s 定时器
    M_TRACE("---------  End test_alarm()  ---------\n\n");
}
