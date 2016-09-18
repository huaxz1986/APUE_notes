/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 vfork 函数的用法
 *
 */
#include"vfork_.h"
#include"../header.h"
#include<fcntl.h>
#include<unistd.h>
extern void print_pid();
extern void print_parent_pid();

void test_vfork()
{
    M_TRACE("---------  Begin test_vfork()  ---------\n");
    assert(prepare_file("test","abc",3,S_IRWXU)==0);
    int fd=My_open("test",O_RDWR);
    if(-1==fd)
    {
        un_prepare_file("test");
        M_TRACE("---------  End test_fork()  ---------\n\n");
        return;
    }
    //****** 打开文件成功 *************//

    int i=0; // 用于测试父子进程是否共享同一个子空间
    int id=vfork();
    if(0==id)
    {//child
        sleep(2);
        fcntl_lock(fd);  // 加锁
        printf("*********** In Child ***********\n");
        print_pid();
        print_parent_pid();
        printf("i=%d\n",i);
        i=999;
        printf("*********** In Child ***********\n");
        fcntl_unlock(fd); // 解锁
        _exit(0);
    }else
    {//parent
        fcntl_lock(fd);  // 加锁
        printf("*********** In Parent ***********\n");
        print_pid();
        print_parent_pid();
        printf("i=%d\n",i);
        printf("*********** In Parent ***********\n");
        fcntl_unlock(fd); // 解锁
    }

    close(fd);
    un_prepare_file("test");
    M_TRACE("---------  End test_vfork()  ---------\n\n");
}
