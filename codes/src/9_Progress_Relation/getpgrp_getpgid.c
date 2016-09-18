/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 getpgrp 函数、getpgid 函数的用法
 *
 */
#include"getpgrp_getpgid.h"
#include"../header.h"

extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid();

pid_t My_getpgrp()
{
    pid_t result=getpgrp();
    printf("progress group id of current progress is %d\n",result);
    return result;
}
pid_t My_getpgid(pid_t pid)
{
    pid_t result=getpgid(pid);
    if(-1==result)
    {
        printf("getpgid(%d) failed,because %s\n",
               pid,strerror(errno));
    }else
    {
        printf("getpgid(%d) ok, progress group id is %d\n",
               pid,result);
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
        My_getpgid(0);// 进程自己
        My_getpgid(getppid());// 父进程
        My_getpgid(1);// init 进程
        My_getpgid(9999);// 不存在的进程
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}

void test_getpgrp_getpgid()
{
    M_TRACE("---------  Begin test_getpgrp_getpgid()  ---------\n");
    create_child();
    // 只有父进程能到达此处
    check_waitpid();
    print_pid();
    print_parent_pid();
    My_getpgrp(); // 父进程自己
    My_getpgid(getppid());// 父进程的父进程
    M_TRACE("---------  End test_getpgrp_getpgid()  ---------\n\n");
}
