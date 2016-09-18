/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sleep 函数、 nano_sleep 函数、 clock_nanosleep 函数的用法
 *
 */
#include"sleep_nanosleep.h"
#include"../header.h"
#include<unistd.h>
#include<signal.h>
typedef void Hanlder_Func (int signo,siginfo_t *info, void *context);
extern void add_sigaction(int signo,sigset_t *set,int no_deffer,int restart,Hanlder_Func handler);


extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid_signal();

unsigned int My_sleep(unsigned int seconds)
{
    unsigned int result=sleep(seconds);
    if(0==result)
    {
        printf("sleep(%d) is finished\n",seconds);
    }else
    {
        printf("sleep(%d) is interrupted,remains %d s.Errno is %s\n",
               seconds,result,strerror(errno));
    }
    return result;
}
int My_nanosleep(const struct timespec *reqtp,struct  timespec *remtp)
{
    int result=nanosleep(reqtp,remtp);
    if(0!=result)
    {
        printf("nanosleep(%p,%p) failed,because %s\n"
               ,reqtp,remtp,strerror(errno));
        if(NULL!=reqtp)
            printf("request time  is:(%d s, %d ns). ",reqtp->tv_sec,reqtp->tv_nsec);
        else
            printf("request time is NULL. ");
        if(NULL!=remtp)
            printf("remain time  is:(%d s, %d ns)\n",remtp->tv_sec,remtp->tv_nsec);
        else
            printf("remain time is NULL\n");
    }else
    {
        printf("nanosleep(%p,%p) is finished, request time is:",reqtp,remtp);
        if(NULL!=reqtp)
            printf("request time  is:(%d s, %d ns). ",reqtp->tv_sec,reqtp->tv_nsec);
        else
            printf("request time is NULL. ");
    }
    return result;
}
int My_clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *reqtp, struct timespec *remtp)
{
    int result=clock_nanosleep(clock_id,flags,reqtp,remtp);
    if(0!=result)
    {
        printf("clock_nanosleep(%d,%d,%p,%p) failed,because %s\n"
               ,clock_id,flags,reqtp,remtp,strerror(errno));
        if(NULL!=reqtp)
            printf("request time  is:(%d s, %d ns). ",reqtp->tv_sec,reqtp->tv_nsec);
        else
            printf("request time is NULL. ");
        if(NULL!=remtp)
            printf("remain time  is:(%d s, %d ns)\n",remtp->tv_sec,remtp->tv_nsec);
        else
            printf("remain time is NULL\n");
    }else
    {
        printf("clock_nanosleep(%d,%d,%p,%p) is finished, request time is:"
               ,clock_id,flags,reqtp,remtp);
        printf("nanosleep(%p,%p) is finished, request time is:",reqtp,remtp);
        if(NULL!=reqtp)
            printf("request time  is:(%d s, %d ns). ",reqtp->tv_sec,reqtp->tv_nsec);
        else
            printf("request time is NULL. ");
    }
    return result;
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
        My_sleep(1); // 让父进程先到达 sleep
        print_pid();
        print_parent_pid();
        My_kill(getppid(),SIGINT); // 向父进程发送信号
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}

void test_sleep_nanosleep()
{
    M_TRACE("---------  Begin test_alarm()  ---------\n");
    add_sigaction(SIGINT,NULL,0,0,sig_print);
    add_sigaction(SIGALRM,NULL,0,0,sig_print);
    create_child();
    // 只有父进程能到达此处
    //My_sleep(3);
    struct timespec request_time;
    struct timespec remain_time;
    request_time.tv_nsec=100;
    request_time.tv_sec=3;
//    My_nanosleep(&request_time,&remain_time);
    My_clock_nanosleep(CLOCK_PROCESS_CPUTIME_ID,0,&request_time,&remain_time); // 相对时间，调用进程的CPU时间
    M_TRACE("---------  End test_alarm()  ---------\n\n");
}
