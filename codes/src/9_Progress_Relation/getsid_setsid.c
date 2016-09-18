/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 getsid 函数、setsid 函数的用法
 *
 */
#include"getsid_setsid.h"
#include"../header.h"

extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid();
extern pid_t My_getpgid(pid_t pid);

pid_t My_setsid()
{
    pid_t result=setsid();
    if(-1==result)
    {
        printf("setsid() failed,because %s\n",
               strerror(errno));
    }
    else
    {
        printf("setsid() ok\n");
        My_getpgid(0);
    }
}

pid_t My_getsid(pid_t pid)
{
    pid_t result=getsid(pid);
    if(-1==result)
    {
        printf("getsid(%d) failed,because %s\n",
               pid,strerror(errno));
    }
    else
    {
        printf("getsid(%d) ok,returns %d\n"
               ,pid,result);
    }
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
        My_getpgid(0);
        My_getsid(0);
        My_setsid();
        My_getsid(0);
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}


void test_getsid_setsid()
{
    M_TRACE("---------  Begin test_getsid_setsid()  ---------\n");
    create_child();
    // 只有父进程能到达此处
    check_waitpid();
    print_pid();
    print_parent_pid();
    My_getpgid(0);
    My_getsid(0);
    My_setsid();
    My_getsid(0);
    M_TRACE("---------  End test_getsid_setsid()  ---------\n\n");
}
