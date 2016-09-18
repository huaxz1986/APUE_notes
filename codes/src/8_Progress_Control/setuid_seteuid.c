/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 setuid 函数、 seteuid 函数、 setgid 函数、setegid 函数 、getlogin 函数的用法
 *
 */
#include"../header.h"
#include"./setuid_seteuid.h"
#include<pwd.h>
extern void print_uid();
extern void print_gid();
extern void print_euid();
extern void print_egid();
extern struct passwd* My_getpwnam(const char *name);

int My_setuid(uid_t uid)
{
    int result=setuid(uid);
    if(-1==result)
    {
        printf("setuid(%d) failed,because %s\n",
               uid,strerror(errno));
    }else
    {
        printf("setuid(%d) ok\n",uid);
    }
    return result;
}
int My_seteuid(uid_t uid)
{
    int result=seteuid(uid);
    if(-1==result)
    {
        printf("seteuid(%d) failed,because %s\n",
               uid,strerror(errno));
    }else
    {
        printf("seteuid(%d) ok\n",uid);
    }
    return result;
}
int My_setgid(gid_t gid)
{
    int result=setgid(gid);
    if(-1==result)
    {
        printf("setgid(%d) failed,because %s\n",
               gid,strerror(errno));
    }else
    {
        printf("setgid(%d) ok\n",gid);
    }
    return result;
}
int My_setegid(gid_t gid)
{
    int result=setegid(gid);
    if(-1==result)
    {
        printf("setegid(%d) failed,because %s\n",
               gid,strerror(errno));
    }else
    {
        printf("setegid(%d) ok\n",gid);
    }
    return result;
}
char* My_getlogin()
{
    char* result=getlogin();
    if(NULL==result)
    {
        printf("getlogin() failed,because %s\n"
               ,strerror(errno));
    }else
    {
        printf("login name is %s\n",result);
    }
    return result;
}



void test_setuid_seteuid()
{
    M_TRACE("---------  Begin test_setuid_seteuid()  ---------\n");
    struct passwd* result=My_getpwnam("huaxz1986");
    if(NULL==result)
    {
        M_TRACE("---------  End test_setuid_seteuid()  ---------\n\n");
        return;
    }

    My_getlogin();
    printf("\n********** Before set id **********\n");
    print_uid();
    print_gid();
    print_euid();
    print_egid();
    printf("\n********** After set id **********\n");
    My_setuid(result->pw_uid); // 二选一
    My_setgid(result->pw_gid); // 二选一
    My_seteuid(result->pw_uid); // 二选一
    My_setegid(result->pw_gid); // 二选一
//    My_setuid(0); // 二选一
//    My_setgid(0); // 二选一
//    My_seteuid(0); // 二选一
//    My_setegid(0); // 二选一
    print_uid();
    print_gid();
    print_euid();
    print_egid();
    M_TRACE("---------  End test_setuid_seteuid()  ---------\n\n");
}
