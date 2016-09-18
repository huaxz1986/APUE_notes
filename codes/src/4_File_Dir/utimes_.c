/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 utimes 函数的用法。 utimensat 函数、 futimens 函数用法类似 utimes 函数用法
 *
 */
#include"utimes_.h"
#include"../header.h"
#include<unistd.h>
#include<fcntl.h>

extern void print_file_time(const char *pathname);
extern int My_access(const char *pathname, int mode);
extern int My_chmod(const char *pathname, mode_t mode);


int My_utimes(const char *pathname, const struct timeval times[])
{
    int result=utimes(pathname,times);
    if(-1==result)
        printf("utimes(\"%s\",%p) failed,because %s\n",pathname,times,strerror(errno));
    else
    {
        printf("utimes(\"%s\",%p) ok\n",pathname,times);
        print_file_time(pathname);
    }
    return result;
}

void test_utimes()
{
    M_TRACE("---------  Begin test_utimes()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0); // 准备 test 文件
    print_file_time("test");
    sleep(2);
    My_access("test",F_OK); // 访问文件，但不修改文件
    print_file_time("test");
    sleep(2);
    My_chmod("test",S_IRUSR|S_IWUSR);//  修改文件状态
    print_file_time("test");

    struct timeval times[2];
    times[0].tv_usec=10;
    times[1].tv_sec=10;
    times[1].tv_usec=10;
    My_utimes("test",times);

    un_prepare_file("test"); // 删除 test 文件
    M_TRACE("---------  End test_utimes()  ---------\n\n");
}
