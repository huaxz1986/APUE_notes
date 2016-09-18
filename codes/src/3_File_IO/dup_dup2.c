/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 * 这里是 dup 函数、dup2 函数的用法
 *
 */
#include"../header.h"
#include"dup_dup2.h"
#include"open_creat.h"


int My_dup(int fd)
{
    int result=dup(fd);
    if(-1==result)
        printf("dup(%d) failed,because %s\n",fd,strerror(errno));
    else
        printf("dup(%d) is %d \n",fd,result);
    return result;
}
int My_dup2(int fd, int fd2)
{
    int result=dup2(fd,fd2);
    if(-1==result)
        printf("dup2(%d,%d) failed,because %s\n",fd,fd2,strerror(errno));
    else
        printf("dup2(%d,%d) is %d \n",fd,fd2,result);
    return result;
}
void test_dup_dup2()
{
    M_TRACE("---------  Begin test_dup_dup2()  ---------\n");
    My_dup(0);  // fd 0 已经被打开的
    My_dup(100); // fd 100 未被打开
    My_dup2(0,0);  // fd 0 已经被打开的
    My_dup2(100,100);  // fd 100 未被打开
    My_dup2(0,100); // fd 0 已经被打开的, fd 100 未被打开
    My_dup2(101,0); // fd 0 已经被打开的, fd 100 未被打开
    M_TRACE("---------  End test_dup_dup2()  ---------\n\n");
}
