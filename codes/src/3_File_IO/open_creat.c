/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 *  这里是 open 和 creat 函数的用法。 openat 用法类似 open
 *
 */
#include"open_creat.h"
#include<stdio.h>
#include<stdarg.h>
#include"../header.h"

int My_open(const char *path, int oflag)
{
    int result=open(path,oflag);
    if(-1==result)
        printf("open(\"%s\",%d) failed,because %s\n",path,oflag,strerror(errno));
    else
        printf("open(\"%s\",%d) return file descriptor %d\n",path,oflag,result);
    return result;
}
int My_open_with_mode(const char *path, int oflag, mode_t mode)
{
    int result=open(path,oflag,mode);
    if(-1==result)
        printf("open(\"%s\",%d,%d) failed,because %s\n",path,oflag,mode,strerror(errno));
    else
         printf("open(\"%s\",%d,%d) return file descriptor %d\n",path,oflag,mode,result);
    return result;
}
int My_creat(const char *path, mode_t mode)
{
    int result=creat(path,mode);
    if(-1==result)
    {
        printf("creat(\"%s\",%d) failed,because %s\n",path,mode,strerror(errno));
    }
    else
         printf("creat(\"%s\",%d) return file descriptor %d\n",path,mode,result);
    return result;
}
void test_open_creat()
{
    M_TRACE("---------  Begin test_open_creat()  ---------\n");
    assert(prepare_file("test1","0123456789",10,S_IRWXU)==0);
    assert(prepare_file("test2","0123456789",10,S_IRWXU)==0);
    assert(prepare_file("test3","0123456789",10,S_IRWXU)==0);
    assert(prepare_file("test4","0123456789",10,S_IRWXU)==0);
    assert(prepare_file("test5","0123456789",10,S_IRWXU)==0);
    un_prepare_file("no_such_file1");
    un_prepare_file("no_such_file2");
    un_prepare_file("no_such_file3");
    un_prepare_file("no_such_file4");
    un_prepare_file("no_such_file5");

    My_open("test1",O_RDWR); // 一个存在的文件
    My_open("no_such_file1",O_RDWR);  // 一个不存在的文件
    My_open_with_mode("test2",O_RDWR,S_IRUSR|S_IWUSR); // 一个存在的文件
    My_open_with_mode("no_such_file2",O_RDWR,S_IRUSR|S_IWUSR); // 一个不存在的文件
    My_open_with_mode("test3",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR); // 一个存在的文件 ，带 O_CREAT 标志
    My_open_with_mode("no_such_file3",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR); // 一个不存在的文件 ，带 O_CREAT 标志
    My_open_with_mode("test4",O_RDWR|O_CREAT|O_EXCL,S_IRUSR|S_IWUSR); // 一个存在的文件 ，带 O_CREAT|O_EXCL 标志
    My_open_with_mode("no_such_file4",O_RDWR|O_CREAT|O_EXCL,S_IRUSR|S_IWUSR); // 一个不存在的文件，带 O_CREAT|O_EXCL 标志
    My_creat("test5",S_IRUSR|S_IWUSR); // 一个存在的文件
    My_creat("no_such_file5",S_IRUSR|S_IWUSR); // 一个不存在的文件

    un_prepare_file("test1");
    un_prepare_file("test2");
    un_prepare_file("test3");
    un_prepare_file("test4");
    un_prepare_file("test5");
    un_prepare_file("no_such_file1");
    un_prepare_file("no_such_file2");
    un_prepare_file("no_such_file3");
    un_prepare_file("no_such_file4");
    un_prepare_file("no_such_file5");
    M_TRACE("---------  End test_open_creat()  ---------\n\n");
}
