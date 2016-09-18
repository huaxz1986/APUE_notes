/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 wait 函数、 waitpid 函数的用法
 *
 */

#include"wait_waitpid.h"
#include"../header.h"
#include<sys/wait.h>
#include<signal.h>

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


pid_t My_wait(int *staloc)
{
    pid_t result=wait(staloc);
    if(result<=0) // 失败返回 0 或者 -1
    {
        printf("wait(%p) failed,because %s\n",
               staloc,strerror(errno));
    }else
    {
        printf("wait(%p) ok, process<pid=%d> terminated.",
               staloc,result);
        if(NULL==staloc)
            printf("\n");
        else    print_return_status(*staloc);
    }
    return result;
}
pid_t My_waitpid(pid_t pid, int *staloc, int options)
{
    pid_t result=waitpid(pid,staloc,options);
    if(result<=0) // 失败返回 0 或者 -1
    {
        printf("waitpid(%d,%p,%d) failed,because %s\n",
               pid,staloc,options,strerror(errno));
    }else
    {
        printf("waitpid(%d,%p,%d) ok, process<pid=%d> terminated.",
               pid,staloc,options,result);
        if(NULL==staloc)
            printf("\n");
        else    print_return_status(*staloc);
    }
    return result;

}
void print_return_status(int staloc)
{
    if(WIFEXITED(staloc))
    {
        printf("return_status:exit normally,exit code is %d\n",
               WEXITSTATUS(staloc));
    }
    if(WIFSIGNALED(staloc))
    {
        printf("return_status:terminate by signal, signal no is %d\n",
               WTERMSIG(staloc));
    }
}

void check_wait()
{
    int status;
    int child_id;
    while((child_id=My_wait(&status))>0) //当wait失败时返回
    {
        ;
    }
}
void check_waitpid()
{
    int status;
    int child_id;
    while((child_id=My_waitpid(-1,&status,0))>0) // 等待所有子进程；阻塞式，一定不能指定 WNOHANG
    {
        ;
    }
}

void check_waitpid_signal()
{
    int status;
    int child_id;
    while((child_id=My_waitpid(-1,&status,0))>0 ||// 等待所有子进程；阻塞式，一定不能指定 WNOHANG
          (child_id<=0 && errno==EINTR))
    {
        ;
    }
}


pid_t child_exit(int fd,int exit_code)
{
    pid_t pid=fork();
    if (0==pid)
    {
        prgress_func(fd,"**********Child_exit***********");
        _exit(exit_code);
        printf("never reached\n");
        return 0;
    }
    return pid;
}
pid_t child_abort(int fd)
{
    pid_t pid=fork();
    if (0==pid)
    {
        prgress_func(fd,"**********Child_abort***********");
        abort();
        printf("never reached\n");
        return 0;
    }
}
pid_t child_signal(int fd)
{
    pid_t pid=fork();
    if (0==pid)
    {
        prgress_func(fd,"**********Child_signal***********");
        kill(getpid(),SIGILL);  //向自己发送 SIGILL信号
        sleep(3); // 确保信号处理程序能执行完毕
        return 0;
    }
    return pid;
}

void test_wait_waitpid()
{
    M_TRACE("---------  Begin test_wait_waitpid()  ---------\n");
    assert(prepare_file("test","abc",3,S_IRWXU)==0);
    int fd=My_open("test",O_RDWR);
    if(-1==fd)
    {
        un_prepare_file("test");
        M_TRACE("---------  End test_fork()  ---------\n\n");
        return;
    }
    //****** 打开文件成功 *************//

    prgress_func(fd,"**********Parent***********");
    if(0!=child_exit(fd,100))
    {// parent
        sleep(1); //确保父进程稍后执行
        if(0!=child_abort(fd))
        {//parent
            sleep(1); //确保父进程稍后执行
            if(0!=child_signal(fd))
            {
                 sleep(1); //确保父进程稍后执行
//                 check_wait();   //only wait at parent （二选一）
                  check_waitpid(); // only wait at parent  （二选一）

                 close(fd);
                 un_prepare_file("test");
                 M_TRACE("---------  End test_wait_waitpid()  ---------\n\n");
            }
        }
    }
}
