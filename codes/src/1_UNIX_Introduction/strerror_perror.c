/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第一章：UNIX 基础知识。
 *
 * 主要是 strerror 函数和 perror 函数的用法
 *
 */
#include"strerror_perror.h"
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include"../header.h"


void test_strerror(int errnum)
{
    M_TRACE("---------  Begin test_strerror(%d)  ---------\n",errnum);
    printf("strerror(%d) output is %s\n",errnum,strerror(errnum));
    M_TRACE("---------  End test_strerror(%d)  ---------\n\n",errnum);
}

void test_perror(int new_errno,const char*msg)
{
    M_TRACE("---------  Begin test_perror(%d,\"%s\")  ---------\n",new_errno,msg);
    int old_errno=errno;  //保存旧值
    errno=new_errno;  // 赋新值
    printf("perror(\"%s\") of errno=%d\n",msg,errno);
    perror(msg);
    errno=old_errno; // 还原旧值
    M_TRACE("---------  End test_perror(%d,\"%s\")  ---------\n\n",new_errno,msg);
}

void test_strerror_perror()
{
        test_perror(EAGAIN,"ppppp");
        test_strerror(EINVAL);
}

