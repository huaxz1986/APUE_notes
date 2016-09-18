/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 setpgid 函数的用法
 *
 */
#include"setpgid_.h"
#include"../header.h"
extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid();
extern pid_t My_getpgrp();

int My_setpgid(pid_t pid, pid_t pgid)
{
    int result=setpgid(pid,pgid);
    if(-1==result)
    {
        printf("setpgid(%d,%d) error,because %s\n"
               ,pid,pgid,strerror(errno));
    }
    else
    {
        printf("setpgid(%d,%d) ok,the new progress group id is %d\n",
               pid,pgid,getpgid(pid));
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
        My_getpgrp(); // 进程自己
        My_setpgid(9999,1) ;// 不存在的进程
        My_setpgid(0,1) ;// 设置本进程
        My_setpgid(0,9999) ;// 设置本进程
        My_setpgid(1,getpgid(0)) ;// 设置 init 进程的进程组ID
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}


void test_setpgid()
{
    M_TRACE("---------  Begin test_setpgid()  ---------\n");
    create_child();
    // 只有父进程能到达此处
    check_waitpid();
    print_pid();
    print_parent_pid();
    My_getpgrp(); // 父进程自己
    M_TRACE("---------  End test_setpgid()  ---------\n\n");
}
