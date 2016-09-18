/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 nice 函数、 getpriority 函数、 setpriority 函数的用法
 *
 */
#include"getpriority_setpriority.h"
#include"../header.h"
#include<unistd.h>


extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid();

int My_nice(int incr)
{
    int result=nice(incr);
    if(-1==result && 0!=errno) //必须要判断：是nice 为-1，还是因为出错导致返回 -1
    {
        printf("nice(%d) failed,because %s\n",
               incr,strerror(errno));
    }else
    {
        printf("nice(%d) ok,new nice value is %d\n",
               incr,result);
    }
    return result;
}
int My_getpriority(int which, id_t who)
{
    int result=getpriority(which,who);
    if(-1==result && 0!=errno) //必须要判断：是nice 为-1，还是因为出错导致返回 -1
    {
        printf("getpriority(%d,%d) failed,because %s\n",
               which,who,strerror(errno));
    }else
    {
        printf("getpriority(%d,%d) ok,new nice value is %d\n",
               which,who,result);
    }
    return result;
}
int My_setpriority(int which, id_t who, int value)
{
    int result=setpriority(which,who,value);
    if(-1==result)
    {
        printf("setpriority(%d,%d,%d) failed,because %s\n",
               which,who,value,strerror(errno));
    }else
    {
        printf("setpriority(%d,%d,%d) ok,the new nice is:%d\n",
               which,who,value,getpriority(which,who));
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
        //******** 设置、读取自己的 nice 值
        printf("Child will set-get self nice:\n");
        My_getpriority(PRIO_PROCESS,0);
        My_nice(9999) ;//提升到 nice 上届
        for(int i=25;i>=-20;i--) //从上界开始下降。到最下界之后会一直保持在下界
        {
            My_nice(-1);
        }
        //******** 设置、读取父进程的 nice 值
        printf("Child will set-get parent nice:\n");
        My_getpriority(PRIO_PROCESS,getppid()); // 父进程的 nice 值
        for(int i=25;i>=-20;i--)
        {
            My_setpriority(PRIO_PROCESS,getppid(),i);
        }
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}

void test_getpriority_setpriority()
{
    M_TRACE("---------  Begin test_getpriority_setpriority()  ---------\n");
    create_child();
    // 只有父进程能到此处
    check_waitpid();
    My_getpriority(PRIO_PROCESS,0); // 父进程自己的 nice 值
    M_TRACE("---------  End test_getpriority_setpriority()  --------\n\n");
}
