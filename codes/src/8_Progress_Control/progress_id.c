/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 getpid 函数、 getppid 函数... 等进程 ID 相关函数的用法
 *
 */
#include"progress_id.h"
#include"../header.h"
#include<unistd.h>

void print_pid()
{
   printf("progress id:%d\n",getpid());
}
void print_parent_pid()
{
    printf("parent progress id:%d\n",getppid());
}
void print_uid()
{
   printf("progress user id:%d\n",getuid());
}
void print_euid()
{
   printf("progress efficient user id:%d\n",geteuid());
}
void print_gid()
{
  printf("progress group id:%d\n",getgid());
}
void print_egid()
{
    printf("progress efficient group id:%d\n",getegid());
}

void test_progress_id()
{
    M_TRACE("---------  Begin test_progress_id()  ---------\n");
    printf("progress ids:\n");
    print_pid();
    print_parent_pid();
    print_uid();
    print_euid();
    print_gid();
    print_egid();
    M_TRACE("---------  End test_progress_id()  ---------\n\n");
}
