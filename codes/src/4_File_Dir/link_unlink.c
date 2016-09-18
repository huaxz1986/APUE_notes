/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 link 函数和 unlink 函数的用法。 linkat 函数用法类似 link 函数用法
 * unlinkat 函数用法类似 unlink 函数用法
 *
 */

#include"link_unlink.h"
#include"../header.h"
#include"stat_lstat.h"
#include<string.h>
#include<errno.h>
#include<unistd.h>

int My_link(const char *existingpath, const char *newpath)
{
    int result=link(existingpath,newpath);
    if(-1==result)
        printf("link(\"%s\",\"%s\") failed,because %s\n",existingpath,newpath,strerror(errno));
    else
    {
        printf("link(\"%s\",\"%s\") ok\n",existingpath,newpath);
        print_file_link_num(existingpath);
    }
    return result;
}
int My_unlink(const char *pathname)
{
    int result=unlink(pathname);
    if(-1==result)
        printf("unlink(\"%s\") failed,because %s\n",pathname,strerror(errno));
    else
    {
        printf("unlink(\"%s\" ) ok\n",pathname);
    }
    return result;
}

void test_link_unlink()
{
    M_TRACE("---------  Begin test_link_unlink()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0); // 准备文件 test
    un_prepare_file("test1"); // 删除文件 test1

    print_file_link_num("test");
    My_link("test","test1");
    My_unlink("test1");
    print_file_link_num("test");
    My_unlink("test1");
    My_unlink("test");
    print_file_link_num("test");

    un_prepare_file("test");
    un_prepare_file("test1");
    M_TRACE("---------  End test_link_unlink()  ---------\n\n");
}
