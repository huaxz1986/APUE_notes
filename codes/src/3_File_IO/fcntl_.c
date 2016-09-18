/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 * 这里是 fcntl 函数的用法
 *
 */
#include"fcntl_.h"
#include"../header.h"
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

extern int My_open(const char *path, int oflag);

int My_fcntl_DUPFD(int fd, int arg)
{
    int result=fcntl(fd,F_DUPFD,arg);
    if(-1==fd)
    {
        printf("fcntl(%d,F_DUPFD,%d) failed,because %s\n",fd,arg,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_DUPFD,%d) returns %d\n",fd,arg,result);
    }
    return result;
}
int My_fcntl_DUPFD_CLOEXEC(int fd, int arg)
{
    int result=fcntl(fd,F_DUPFD_CLOEXEC,arg);
    if(-1==fd)
    {
        printf("fcntl(%d,F_DUPFD_CLOEXEC,%d) failed,because %s\n",fd,arg,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_DUPFD_CLOEXEC,%d) returns %d\n",fd,arg,result);
    }
    return result;
}
int My_fcntl_GETFD(int fd)
{
    int result=fcntl(fd,F_GETFD);
    if(-1==fd)
    {
        printf("fcntl(%d,F_GETFD) failed,because %s\n",fd,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_GETFD) returns %d\n",fd,result);
    }
    return result;
}
int My_fcntl_SETFD(int fd, int arg)
{
    int result=fcntl(fd,F_SETFD,arg);
    if(-1==fd)
    {
        printf("fcntl(%d,F_SETFD,%d) failed,because %s\n",fd,arg,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_SETFD,%d) returns %d\n",fd,arg,result);
    }
    return result;
}
int My_fcntl_GETFL(int fd)
{
    int result=fcntl(fd,F_GETFL);
    if(-1==fd)
    {
        printf("fcntl(%d,F_GETFL) failed,because %s\n",fd,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_GETFL) returns %d\n",fd,result);
    }
    return result;
}
int My_fcntl_SETFL(int fd, int arg)
{
    int result=fcntl(fd,F_SETFL,arg);
    if(-1==fd)
    {
        printf("fcntl(%d,F_SETFL,%d) failed,because %s\n",fd,arg,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_SETFL,%d) returns %d\n",fd,arg,result);
    }
    return result;
}
int My_fcntl_GETOWN(int fd)
{
    int result=fcntl(fd,F_GETOWN);
    if(-1==fd)
    {
        printf("fcntl(%d,F_GETOWN) failed,because %s\n",fd,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_GETOWN) returns %d\n",fd,result);
    }
    return result;
}
int My_fcntl_SETOWN(int fd, int arg)
{
    int result=fcntl(fd,F_SETOWN,arg);
    if(-1==fd)
    {
        printf("fcntl(%d,F_SETOWN,%d) failed,because %s\n",fd,arg,strerror(errno));
    }else
    {
        printf("fcntl(%d,F_SETOWN,%d) returns %d\n",fd,arg,result);
    }
    return result;
}
void print_fl(int fd, int flag)
{

    /*文件状态标志必须首先用屏蔽字 `O_ACCMODE` 取得访问方式位，
     * 然后与`O_RDONLY`、`O_WRONLY`、`O_RDWR`、`O_EXEC`、`O_SEARCH`比较（这5个值互斥，且并不是各占1位）。
     * 剩下的还有：`O_APPEND`、`O_NONBLOCK`、`O_SYNC`
     */
    printf("flag on fd(%d):",fd);
    if(flag&O_APPEND) printf("\tO_APPEND;");
    if(flag&O_NONBLOCK) printf("\tO_NONBLOCK;");
    if(flag&O_SYNC) printf("\tO_SYNC;");
    if(flag&O_DSYNC) printf("\tO_DSYNC;");
    if(flag&O_RSYNC) printf("\tO_RSYNC;");
    if(flag&O_FSYNC) printf("\tO_FSYNC;");
    if(flag&O_ASYNC) printf("\tO_ASYNC;");
    switch (flag&O_ACCMODE) {
    case O_RDONLY:
        printf("\tO_RDONLY;");
        break;
    case O_WRONLY:
        printf("\tO_WRONLY;");
        break;
    case O_RDWR:
        printf("\t\tO_RDWR;");
        break;
    default:
        printf(" can never come here\n");
        break;
    }
    printf("\n");
}
void test_fcntl()
{
    M_TRACE("---------  Begin test_fcntl()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);

    int fd=My_open("test",O_WRONLY);
    if(-1==fd) // 打开文件失败
        return ;
    //测试 My_fcntl_GETFD 和 My_fcntl_DUPFD、My_fcntl_DUPFD_CLOEXEC
    My_fcntl_GETFD(My_fcntl_DUPFD(fd,10));
    My_fcntl_GETFD(My_fcntl_DUPFD(fd,0));
    My_fcntl_GETFD(My_fcntl_DUPFD_CLOEXEC(fd,10));
    My_fcntl_GETFD(My_fcntl_DUPFD_CLOEXEC(fd,0));
    // 测试 My_fcntl_GETFD、My_fcntl_SETFD
    My_fcntl_GETFD(fd);
    My_fcntl_SETFD(fd,~FD_CLOEXEC);
    My_fcntl_GETFD(fd);
    My_fcntl_SETFD(fd,FD_CLOEXEC);
    My_fcntl_GETFD(fd);
    // 测试 My_fcntl_GETFL、My_fcntl_SETFL
    print_fl(fd,My_fcntl_GETFL(fd));
    My_fcntl_SETFL(fd,O_RDWR);
    print_fl(fd,My_fcntl_GETFL(fd));
    My_fcntl_SETFL(fd,O_RDONLY|O_NONBLOCK);
    print_fl(fd,My_fcntl_GETFL(fd));
    // 测试 My_fcntl_GETOWN、My_fcntl_SETOWN
    My_fcntl_GETOWN(fd);
    My_fcntl_SETOWN(fd,1);
    My_fcntl_GETOWN(fd);
    close(fd);
    un_prepare_file("test");
    M_TRACE("---------  End test_fcntl()  ---------\n\n");
}
