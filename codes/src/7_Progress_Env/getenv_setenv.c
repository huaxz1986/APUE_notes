/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 getenv 函数、putenv 函数、setenv 函数、 unsetenv 函数，以及全局变量 environ 的用法。
 *
 */
#include"getenv_setenv.h"
#include"../header.h"
#include<stdlib.h>

extern char **environ; // 环境变量

char* My_getenv(const char *name)
{
    char* result=getenv(name);
    if(NULL==result)
    {
        printf("getenv(\"%s\") failed,because %s\n",
               name,strerror(errno));
    }else
    {
        printf("getenv(\"%s\") ok,value is \"%s\"\n",
               name,result);
    }
}
int My_putenv(char *str)
{
    int result=putenv(str);
    if(0!=result)
    {
        printf("putenv(\"%s\") failed,because %s\n",
               str,strerror(errno));
    }else
    {
        printf("putenv(\"%s\") ok\n",str);
    }
    return result;
}
int My_setenv(const char *name, const char *value, int rewrite)
{
    int result=setenv(name,value,rewrite);
    if(-1==result)
    {
        printf("setenv(\"%s\",\"%s\",%d) failed,because %s\n",
               name,value,rewrite,strerror(errno));
    }else
    {
        printf("setenv(\"%s\",\"%s\",%d) ok\n",name,value,rewrite);
    }
    return result;
}
int My_unsetenv(const char *name)
{
    int result=unsetenv(name);
    if(-1==result)
    {
        printf("unsetenv(\"%s\") failed,because %s\n",
               name,strerror(errno));
    }else
    {
        printf("unsetenv(\"%s\") ok\n",name);
    }
    return result;
}

void print_environ()
{
    printf("Environment:\"");
    char **ptr=environ;

    while(*ptr!=NULL)
    {
        printf("%s;\t",*ptr);
        ptr++;
    }
    printf("\"\n");
}
void test_getenv_setenv()
{
    M_TRACE("---------  Begin test_getenv_setenv()  ---------\n");
    print_environ();
    //********* 测试 getenv ******//
    printf("******* test getenv *******\n");
    My_getenv("HOME");
    My_getenv("LANG");
    My_getenv("PATH");
    //********* 测试 setenv ,putenv ******//
    printf("\n\n******* test setenv ,putenv *******\n");
    My_putenv("aaa"); // 不正常的格式
    My_getenv("aaa");
    My_putenv("aaa=1"); // 正常的格式
    My_getenv("aaa");
    My_setenv("aaa","2",0); // 不覆盖
    My_getenv("aaa");
    My_setenv("aaa","2",1); // 覆盖
    My_getenv("aaa");
    //********* 测试 unsetenv ******//
    printf("\n\n******* test unsetenv *******\n");
    My_unsetenv("bbb"); //不存在
    My_unsetenv("aaa");
    M_TRACE("---------  End test_getenv_setenv()  ---------\n\n");
}
