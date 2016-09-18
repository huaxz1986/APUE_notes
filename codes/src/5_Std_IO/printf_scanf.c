/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 printf 函数、snprintf 函数、 scanf 函数、sscanf 函数 的用法。
 * fprintf 函数、 dprintf 函数的用法类似 printf 函数。
 * sprintf 函数的用法类似 snprintf 函数。
 * fscanf 函数的用法类似 scanf 函数。
 *
 *
 */
#include"printf_scanf.h"
#include"../header.h"
#include<stdio.h>
void _test_printf()
{
    int ok=printf("%d,%c,%f,%s\n",99,'z',0.99,"hello");
    if(ok<0) printf("printf failed,because %s\n",strerror(errno));
    else printf("printf ok\n");
}
void _test_snprintf()
{
    char buffer[128];
    int ok=snprintf(buffer,128,"%d,%c,%f,%p,%s",99,'z',0.99,buffer,"hello");
    if(ok<0)
    {
        printf("snprintf error,because:%s\n",strerror(errno));
    }else
    {
        printf("snprintf ok, write %d chars\n",ok);
        print_char_buffer(buffer,128);
     }
}

void _test_scanf()
{
    int i;
    char c;
    float d;
    char *s;
    int ok=scanf("%d,%c,%f,%ms",&i,&c,&d,&s);
    if(EOF==ok)
    {
        if(ferror(stdin))
            printf("scanf is error,because %s\n",strerror(errno));
        else if(feof(stdin))
            printf("scanf read EOF\n");
    }else
    {
        printf("scanf ok,return %d items\n",ok);
        printf("items are:%d,%c,%f,%s\n",i,c,d,s);
        free(s);
    }
}
void _test_sscanf()
{
    char buffer[128];
    int ok=snprintf(buffer,128,"%d,%c,%f,%p,%s",99,'z',0.99,buffer,"hello");
    assert(ok>=0);
    int i;
    char c;
    float d;
    char *s;
    void *addr;
    ok=sscanf(buffer,"%d,%c,%f,%p,%ms",&i,&c,&d,&addr,&s);
    if(EOF==ok)
    {
        if(ferror(stdin))
            printf("sscanf is error,because %s\n",strerror(errno));
        else if(feof(stdin))
            printf("sscanf read EOF\n");
    }else
    {
        printf("sscanf ok,return %d items\n",ok);
        printf("items are:%d,%c,%f,%p,%s\n",i,c,d,addr,s);
        free(s);
    }
}
void test_printf_scanf()
{
    M_TRACE("---------  Begin test_printf_scanf()  ---------\n");
    printf("**** test printf  *******\n");
    _test_printf();
    printf("\n\n**** test snprintf  *******\n");
    _test_snprintf();
    printf("\n\n**** test scanf  *******\n");
    _test_scanf();
    printf("\n\n**** test sscanf  *******\n");
    _test_sscanf();
    M_TRACE("---------  End test_printf_scanf()  ---------\n\n");
}
