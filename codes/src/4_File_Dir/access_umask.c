/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 access 函数和 umask 函数的用法。 faccess 函数用法类似 access 函数用法
 *
 */
#include"access_umask.h"
#include"../header.h"
#include<unistd.h>


int My_access(const char *pathname, int mode)
{
    int result=access(pathname,mode);
    if(-1==result)
        printf("access(\"%s\",%d) failed,because %s\n",pathname,mode,strerror(errno));
    else
        printf("access(\"%s\",%d) ok\n",pathname,mode);
    return result;
}
mode_t My_umask(mode_t cmask)
{
    mode_t result=umask(cmask);
    printf("umask ok , cmask is :<"); // umask 没有失败值
    print_mode_perms(cmask,"");
    printf(">\t, old umask is :<");
    print_mode_perms(result,"");
    printf(">\n");
    return result;
}

void test_access_umask()
{
    M_TRACE("---------  Begin test_access_umask()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);

    My_access("/no/exist",F_OK); // no exist
    My_access("/etc/shadow",W_OK);// can not write
    My_access("test",W_OK); // can write

    assert(prepare_file("test_umask1",NULL,0,S_IRWXU)==0);// old umask
    print_file_perm("test_umask1");
    //new umask
    mode_t old_mask=My_umask(S_IRUSR|S_IRGRP|S_IROTH);
    assert(prepare_file("test_umask2",NULL,0,S_IRWXU)==0);// old umask
    print_file_perm("test_umask2");
    umask(old_mask); // 恢复原值。否则后续生成的测试文件不可写！！！

    un_prepare_file("test");
    un_prepare_file("test_umask1");
    un_prepare_file("test_umask2");
    M_TRACE("---------  End test_access_umask()  ---------\n\n");
}

