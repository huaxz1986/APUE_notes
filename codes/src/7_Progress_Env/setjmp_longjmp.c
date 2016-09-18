/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 setjmp 函数、 longjmp 函数的用法
 *
 */
#include"setjmp_longjmp.h"
#include"../header.h"
static jmp_buf buf; // static 全局变量

void print_jmp_buf(const jmp_buf env)
{
    printf("jmp_buf is :");
    for(int i=0;i<8;i++)
    {
       printf("%d,",env[0].__jmpbuf[i]);
    }
    printf("\n");
}

void My_longjmp(jmp_buf env, int val)
{
    printf("longjmp with val=%d\n",val);
    longjmp(env,val);
}

static int global_int; // static 全局变量，用于观察跨 longjmp 之后全局变量是否回滚

void test_setjmp_longjmp()
{
    M_TRACE("---------  Begin test_setjmp_longjmp()  ---------\n");
    char local_char='a'; // 局部变量，用于观察跨 longjmp 之后全局变量是否回滚

    print_jmp_buf(buf);
    int val;
    //********** setjmp ***********//
    val=setjmp(buf);
    if(0==val)
    {
         printf("setjmp called directly,return %d. global_int=%d,local_char=%c\n",val,global_int,local_char);
         print_jmp_buf(buf);
    }
    else
    {
        printf("setjmp called from longjmp,return %d. After longjmp:global_int=%d,local_char=%c\n",val,global_int,local_char);
        print_jmp_buf(buf);
    }
    //*********** longjmp *********//
    if(0==val)
    {
        printf("setjmp must returns 0\n");
        global_int=19;  // longjmp 之前的 global_int
        local_char='b'; // longjmp 之前的 local_char
        printf("longjmp with val=%d.Before longjmp:global_int=%d,local_char=%c\n",1,global_int,local_char);
        longjmp(buf,1);
    }else if(1==val)
    {
        printf("setjmp must returns 1\n");
        global_int=29;  // longjmp 之前的 global_int
        local_char='c'; // longjmp 之前的 local_char
        printf("longjmp with val=%d.Before longjmp:global_int=%d,local_char=%c\n",1,global_int,local_char);
        longjmp(buf,2);
    }else
    {
        printf("setjmp must returns no 0,1\n");
    }
    M_TRACE("---------  End test_setjmp_longjmp()  ---------\n\n");
}
