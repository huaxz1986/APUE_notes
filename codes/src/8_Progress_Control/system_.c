/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 system 函数的用法
 *
 */
#include"system_.h"
#include"../header.h"
#include<stdlib.h>

extern void print_return_status(int staloc);

int My_system(const char *cmdstring)
{
    int result=system(cmdstring);
    if(-1==result)
    {
        printf("system(\"%s\") failed,because fork error or waitpid error :(%s)\n",
               cmdstring,strerror(errno));
    }else if(WIFEXITED(result) && 127==WEXITSTATUS(result)) // 其返回值如同`shell`执行了`exit(127)`一样
    {
        printf("system(\"%s\") failed,because shell can not run cmdstring\n",
               cmdstring);
        print_return_status(result);
    }else
    {
        printf("system(\"%s\")  ok\n",cmdstring);
        print_return_status(result);
    }
    return result;
}

void test_system()
{
    M_TRACE("---------  Begin test_system()  ---------\n");
    My_system("ls /home"); //命令存在
    My_system("ttttt"); // 不存在命令
    M_TRACE("---------  End test_system()  ---------\n\n");
}
