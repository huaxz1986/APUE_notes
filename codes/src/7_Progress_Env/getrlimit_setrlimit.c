/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 getrlimit 函数、 setrlimit 函数的用法
 *
 */
#include"getrlimit_setrlimit.h"
#include"../header.h"

void print_rlimit(const struct rlimit *rlptr)
{
    printf("rlimit is:");
    if(NULL==rlptr)
    {
        printf("\tNULL\n");
        return;
    }
    printf("cur_limit=%d;\t max_limit=%d \n",
           rlptr->rlim_cur,rlptr->rlim_max);
}
int My_getrlimit(int resource, struct rlimit *rlptr)
{
    int result=getrlimit(resource,rlptr);
    if(0!=result)
    {
        printf("getrlimit(%d,%p) failed,because %s\n",
               resource,rlptr,strerror(errno));
    }else
    {
        printf("getrlimit(%d,%p) ok:",resource,rlptr);
        print_rlimit(rlptr);
    }
    return result;
}
int My_setrlimit(int resource, struct rlimit *rlptr)
{
    int result=setrlimit(resource,rlptr);
    if(0!=result)
    {
        printf("setrlimit(%d,%p) failed,because %s\n",
               resource,rlptr,strerror(errno));
    }else
    {
        printf("setrlimit(%d,%p) ok\n",resource,rlptr);
    }
    return result;
}

void test_getrlimit_setrlimit()
{
    M_TRACE("---------  Begin test_getrlimit_setrlimit()  ---------\n");
    struct rlimit buf;
    //************ 测试 getrlimit ***********//
    printf("*********** test getrlimit ***********\n");
    My_getrlimit(RLIMIT_CORE,&buf);
    My_getrlimit(RLIMIT_CPU,&buf);
    My_getrlimit(RLIMIT_FSIZE,&buf);
    My_getrlimit(RLIMIT_MEMLOCK,&buf);
    My_getrlimit(RLIMIT_MSGQUEUE,&buf);
    My_getrlimit(RLIMIT_NICE,&buf);
    My_getrlimit(RLIMIT_NPROC,&buf);
    My_getrlimit(RLIMIT_SIGPENDING,&buf);
    //************ 测试 setrlimit ***********//
    printf("\n\n*********** test getrlimit ***********\n");
    buf.rlim_cur=1;
    buf.rlim_max=10;
    My_setrlimit(RLIMIT_NICE,&buf);
    My_getrlimit(RLIMIT_NICE,&buf);
    M_TRACE("---------  End test_getrlimit_setrlimit()  ---------\n\n");
}
