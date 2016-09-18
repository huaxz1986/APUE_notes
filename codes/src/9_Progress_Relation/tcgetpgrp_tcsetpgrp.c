/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 tcgetpgrp 函数、tcsetpgrp 函数、tcgetsid 函数的用法
 *
 */

#include"tcgetpgrp_tcsetpgrp.h"
#include"../header.h"
#include<termios.h>
extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid();
extern pid_t My_getpgrp();
extern pid_t My_getsid(pid_t pid);

pid_t My_tcgetpgrp(int fd)
{
    pid_t result=tcgetpgrp(fd);
    if(-1==result)
    {
        printf("tcgetpgrp(%d) failed,because %s\n",
               fd,strerror(errno));
    }else
    {
        printf("tcgetpgrp(%d) ok, front progress group id is %d\n",
               fd,result);
    }
    return result;
}
int My_tcsetpgrp(int fd, pid_t pgrpid)
{
    int result=tcsetpgrp(fd,pgrpid);
    if(-1==result)
    {
        printf("tcsetpgrp(%d,%d) failed,because %s\n",
               fd,pgrpid,strerror(errno));
    }else
    {
        printf("tcsetpgrp(%d,%d) ok, front progress group id is %d\n",
               fd,pgrpid,tcgetpgrp(fd));
    }
    return result;
}
pid_t My_tcgetsid(int fd)
{
    pid_t result=tcgetsid(fd);
    if(-1==result)
    {
        printf("tcgetsid(%d) failed,because %s\n",
               fd,strerror(errno));
    }else
    {
        printf("tcgetsid(%d) ok, session id is %d\n",
               fd,result);
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
        My_getpgrp(); // 进程的进程组 ID
        My_getsid(0);  // 会话 ID
        My_tcgetsid(0) ;// fd0 的会话 ID
        My_tcgetpgrp(0);// fd0 的前端进程组 ID
        My_tcsetpgrp(0,getppid()-2) ;// 进程继承体系之外
        My_tcsetpgrp(0,getsid(0)) ;// 父进程ID
        My_getpgrp(); // 进程的进程组 ID
        My_getsid(0);  // 会话 ID
        My_tcgetsid(0) ;// fd0 的会话 ID
        My_tcgetpgrp(0);// fd0 的前端进程组 ID
        printf("************ In Child **********\n");
        _exit(0); //_exit 退出
    }
    return pid;
}

void test_tcgetpgrp_tcsetpgrp()
{
    M_TRACE("---------  Begin test_tcgetpgrp_tcsetpgrp()  ---------\n");
    create_child();
    // 只有父进程能到达此处
    check_waitpid();
    print_pid();
    print_parent_pid();
    My_getpgrp(); // 父进程自己
    M_TRACE("---------  End test_tcgetpgrp_tcsetpgrp()  ---------\n\n");
}
