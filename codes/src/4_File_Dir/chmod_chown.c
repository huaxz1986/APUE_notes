/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 chmod 函数和 chown 函数的用法。 fchown 函数、 fchown函数、  lchown用法类似 chown 函数用法。
 * fchmod 函数、 fchmodat 函数用法类似 chmod 函数。
 *
 */
#include"chmod_chown.h"
#include"../header.h"
#include<unistd.h>
#include<string.h>
#include<errno.h>

extern void print_file_perm(const char*pathname);
extern void print_file_owner(const char*pathname);

int My_chmod(const char *pathname, mode_t mode)
{
    int result=chmod(pathname,mode);
    if(-1==result)
        printf("chmod(\"%s\",%d) failed,because %s\n",pathname,mode,strerror(errno));
    else
    {
        printf("chmod(\"%s\",%d) ok\n",pathname,mode);
        print_file_perm(pathname);
    }
    return result;
}
int My_chown(const char *pathname, uid_t owner, gid_t group)
{
    int result=chown(pathname,owner,group);
    if(-1==result)
        printf("chown(\"%s\",%d,%d) failed,because %s\n",pathname,owner,group,strerror(errno));
    else
    {
        printf("chown(\"%s\",%d,%d) ok\n",pathname,owner,group);
        print_file_owner(pathname);
    }
    return result;
}
void test_chmod_chown()
{
    M_TRACE("---------  Begin test_chmod_chown()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);

    const char *file_name="test";
    Stat buf;

    My_stat(file_name,&buf);
    My_chmod(file_name,S_IRWXU);
    My_chown(file_name,1,1);

    un_prepare_file("test");
    M_TRACE("---------  End test_chmod_chown()  ---------\n\n");
}
