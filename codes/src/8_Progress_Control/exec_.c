/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 exec 函数族的用法
 *
 */
#include"exec_.h"
#include"../header.h"
#include<unistd.h>


void _test_execl(const char* pathname)
{
    if(fork()==0)
    {//child
        if(-1== execl(pathname,"execl_arg1","execl_arg2",(char *) 0))
        printf("execl error ,because %s\n",strerror(errno));
        _exit(-1);
    }
}
void _test_execv(const char* pathname)
{
    char *argv[3];
    argv[0]="execv_arg1";
    argv[1]="execv_arg2";
    argv[2]=NULL;
    if(fork()==0)
    {//child
        if(-1==execv(pathname,argv))
        {
            printf("execv error ,because %s\n",strerror(errno));
        }
        _exit(-1);
    }
}
void _test_execle(const char* pathname)
{
    char *envp[3];
    envp[0]="execle_env1=1";
    envp[1]="execle_env2=2";
    envp[2]=NULL;
    if(fork()==0)
    {//child
        if(-1== execle(pathname,"execle_arg1",
        "execle_arg2",(char *) 0,envp))
        printf("execle error ,because %s\n",strerror(errno));
        _exit(-1);
    }
}
void _test_execve(const char* pathname)
{
    char *argv[3];
    argv[0]="execve_arg1";
    argv[1]="execve_arg2";
    argv[2]=NULL;
    char *envp[3];
    envp[0]="execve_env1=1";
    envp[1]="execve_env2=2";
    envp[2]=NULL;
    if(fork()==0)
    {//child
        if(-1== execve(pathname,argv,envp))
            printf("execve error ,because %s\n",strerror(errno));
        _exit(-1);
    }
}
void _test_execlp(const char* filename)
{
    if(fork()==0)
    {//child
        if(-1== execlp(filename,"execlp_arg1","execlp_arg2",(char *) 0))
            printf("execlp error ,because %s\n",strerror(errno));
        _exit(-1);
    }
}
void _test_execvp(const char* filename)
{
    char * argv[3];
    argv[0]="execvp_arg1";
    argv[1]="execvp_arg2";
    argv[2]=NULL;
    if(fork()==0)
    {//child
        if(-1== execvp(filename,argv))
            printf("execvp error ,because %s\n",strerror(errno));
        _exit(-1);
    }
}

void test_exec()
{
    M_TRACE("---------  Begin test_exec()  ---------\n");
    char buffer[1024];
    getcwd(buffer,1024);
    char *pathname=abs_path(buffer,"print_arg");

    _test_execl(pathname); // 绝对路径名
    _test_execv(pathname); // 绝对路径名
    _test_execle(pathname); // 绝对路径名
    _test_execve(pathname); // 绝对路 径名
    _test_execlp("print_arg"); //相对文件名
    _test_execvp("print_arg"); //相对文件名
    M_TRACE("---------  End test_exec()  ---------\n\n");
}


//************* print_arg 程序的源代码 **********//
//                                             //
// 该程序的功能是打印环境变量以及参数列表            //
//                                            //
//********************************************//

//#include <stdio.h>
//#include<stdlib.h>
//#include<unistd.h>
//extern char **environ;
//void print_environ()
//{
//    printf("\t************Environment***************\n");
//    char **ptr=environ;
//    while(*ptr!=NULL)
//    {
//        printf("\t'%s'",*ptr);
//        ptr++;
//    }
//    printf("\n");
//}
//int main(int argc, char *argv[])
//{
//    printf("\t************Argument List***************\n");
//    for(int i=0;i<argc;i++)
//    {
//        printf("\t'%s'",argv[i]);
//    }
//    printf("\n");
//    print_environ();
//    return 0;
//}
