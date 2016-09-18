/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第七章：进程环境
 *
 * 测试 malloc 函数、 calloc 函数、realloc 函数的用法。
 *
 */
#include"malloc_realloc.h"
#include"../header.h"
#include<time.h>
void* My_malloc(size_t size)
{
    void *result=malloc(size);
    if(NULL==result)
    {
        printf("malloc(%d) failed,because %s\n",
               size,strerror(errno));
    }else
    {
        printf("malloc(%d) ok,return %p\n",size,result);
    }
    return result;
}
void* My_calloc(size_t nobj, size_t size)
{
    void *result=calloc(nobj,size);
    if(NULL==result)
    {
        printf("calloc(%d,%d) failed,because %s\n",
               nobj,size,strerror(errno));
    }else
    {
        printf("calloc(%d,%d) ok,return %p\n",
               nobj,size,result);
    }
    return result;
}
void* My_realloc(void *ptr, size_t newsize)
{
    void *result=realloc(ptr,newsize);
    if(NULL==result)
    {
        printf("realloc(%p,%d) failed,because %s\n",
               ptr,newsize,strerror(errno));
    }else
    {
        printf("realloc(%p,%d) ok,return %p\n",
               ptr,newsize,result);
    }
    return result;
}
void test_malloc_realloc()
{
    M_TRACE("---------  Begin test_malloc_realloc()  ---------\n");
    free(NULL); //测试 free(NULL)
    void * ptr1;
    void * ptr2;
    void * ptr3;
    void * ptr4;
    void * ptr5;

    //************ 执行测试 ***************//
    ptr1=My_malloc(10);
    ptr2=My_calloc(sizeof(struct timespec),10);
    ptr3=My_realloc(ptr1,5); // 缩小
    ptr4=My_realloc(ptr3,1000); // 扩大，ptr1！=ptr3(ptr1 释放掉，ptr3 重新分配)
    ptr5=My_realloc(NULL,100); //等价于 malloc(100)
    //************* 释放内存 **************//
    free(ptr5); // ok ，因为是新分配的
    free(ptr4);
    free(ptr2); // ok， 因为是新分配的
//    free(ptr1); // 错误：因为 ptr1=ptr3，而 ptr3指向的内存在 My_realloc(ptr3,1000) 时被释放
//    free(ptr3);// 错误：因为 ptr1=ptr3，而 ptr3指向的内存在 My_realloc(ptr3,1000) 时被释放
    M_TRACE("---------  End test_malloc_realloc()  ---------\n\n");
}
