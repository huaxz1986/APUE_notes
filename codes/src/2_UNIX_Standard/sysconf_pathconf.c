/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第二章：UNIX 标准及实现。
 *
 * 主要是 sysconf 函数、pathconf函数、以及 fpathconf 函数的用法
 *
 */
#include"sysconf_pathconf.h"
#include"../header.h"
#include<stdalign.h>
#include<unistd.h>



long My_pathconf(const char *pathname, int name,const char*name_str)
{
    long result=pathconf(pathname,name);
    if(-1==result)
    {
        printf("'pathconf(\"%s\",%s)' failed,because %s\n", pathname,name_str,strerror(errno));
    }else
        printf("sysconf(%s) is %d\n",name_str,result);
    return result;
}
long My_sysconf(int name,const char*name_str)
{
    long result=sysconf(name);
    if(-1==result)
    {
        printf("'sysconf(%s)' failed,because %s\n", name_str,strerror(errno));
    }else
        printf("sysconf(\"%s\") is %d\n",name_str,result);
    return result;
}
void test_sycconf_pathconf()
{
        M_TRACE("---------  Begin test_sycconf_pathconf()  ---------\n");
        assert(prepare_file("test",NULL,0,0)==0);

        My_sysconf(_SC_ARG_MAX,"ARG_MAX");
        My_sysconf(_SC_PAGESIZE,"PAGESIZE");
        My_pathconf("test",_PC_NAME_MAX,"NAME_MAX");  // 文件 '/home/huaxz1986/APUE/main.c' 必须存在
        My_pathconf("test",_PC_PIPE_BUF,"PIIPE_BUF"); // 文件 '/home/huaxz1986/APUE/main.c' 必须存在

        un_prepare_file("test");
        M_TRACE("---------  End test_sycconf_pathconf()  ---------\n\n");
}
