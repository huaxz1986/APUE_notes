/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 fork 函数的用法
 *
 */
#include"fork_.h"
#include"../header.h"
#include<unistd.h>
#include<fcntl.h>

extern int My_open(const char *path, int oflag);
extern void print_pid();
extern void print_parent_pid();

/*!
 * \brief prgress_func : 完成每个进程中的主要工作
 * \param fd : 打开的文件描述符，用于记录锁
 * \param append_str : 说明每个进程的字符串
 */
static void prgress_func(int fd,const char* append_str)
{
    fcntl_lock(fd);  // 加锁
    printf("%s\n",append_str);
    print_pid();
    print_parent_pid();
    printf("%s\n",append_str);
    fcntl_unlock(fd); // 解锁
}
void test_fork()
{
    M_TRACE("---------  Begin test_fork()  ---------\n");
    assert(prepare_file("test","abc",3,S_IRWXU)==0);
    int fd=My_open("test",O_RDWR);
    if(-1==fd)
    {
        un_prepare_file("test");
        M_TRACE("---------  End test_fork()  ---------\n\n");
        return;
    }
    //****** 打开文件成功 *************//
    pid_t id=fork();
    if(0==id)
    { // child 1
        prgress_func(fd,"**********In Child 1***********");
        _exit(0);
    }
    sleep(2); // 确保父进程在子进程之后执行
    id=fork();
    printf("This is in the second fork\n");
    if(0==id)
    {// child 2
        prgress_func(fd,"**********In Child 2***********");
        _exit(0);
    }
    sleep(2);  // 确保父进程在子进程之后执行
    prgress_func(fd,"**********In Parent***********");

    close(fd);
    un_prepare_file("test");
    M_TRACE("---------  End test_fork()  ---------\n\n");
}
