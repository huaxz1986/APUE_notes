/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 tmpnam 函数、mkdtemp 函数的用法。
 * tmpfile 函数的用法类似 tmpnam 函数。
 * mkstemp 函数的用法类似 mkdtemp 函数。
 *
 *
 */
#include"tmpnam_mkdtemp.h"
#include"../header.h"

extern void print_file_type(const char*pathname);
extern void print_file_perm(const char *pathname);
extern void print_file_time(const char *pathname);
extern int My_unlink(const char *pathname);
extern int My_rmdir(const char *pathname);

char * My_tmpnam(char *ptr)
{
    char*result=tmpnam(ptr);
    if(NULL==result)
        printf("tmpnam(%p) failed,because %s\n",ptr,strerror(errno));
    else
        printf("tmpnam(%p) ok,temp file name is \"%s\"\n",ptr,result);
    return result;
}

char* My_mkdtemp(char* tmplate)
{
    char*result=mkdtemp(tmplate);
    if(NULL==result)
        printf("mkdtemp(\"%s\") failed,because %s\n",tmplate,strerror(errno));
    else
        printf("mkdtemp(\"%s\") ok,temp file name is \"%s\"\n",tmplate,result);
    return result;
}

void _test_tmpnam()
{
    char buffer1[1024];
    char buffer2[1024];
    char* temp_file1=My_tmpnam(buffer1);
    if(NULL!=temp_file1) // 只是创建临时文件名，而并没有创建文件
        My_unlink(temp_file1);

    //****** 第二次创建临时文件 ****//
    char* temp_file2=My_tmpnam(buffer2);
    if(NULL!=temp_file2) // 只是创建临时文件名，而并没有创建文件
        My_unlink(temp_file2);
}
void _test_mkdtemp()
{
    char buffer1[128]="AAAXXXXXX";
    char buffer2[128]="BBBXXXXXX";

    char *temp_dir1=My_mkdtemp(buffer1); //因为会修改 buffer1，因此不能用字符串常量
    print_file_type(temp_dir1);
    print_file_perm(temp_dir1);
    print_file_time(temp_dir1);
    if(NULL!=temp_dir1)
        My_rmdir(temp_dir1);
    //****** 第二次创建临时目录 ****//
    char *temp_dir2=My_mkdtemp(buffer2); //因为会修改 buffer2，因此不能用字符串常量
    print_file_type(temp_dir2);
    print_file_perm(temp_dir2);
    print_file_time(temp_dir2);
    if(NULL!=temp_dir2)
        My_rmdir(temp_dir2);
}

void test_tmpnam_mkdtemp()
{
    M_TRACE("---------  Begin test_printf_scanf()  ---------\n");
    printf("******** test tmpnam ********\n");
    _test_tmpnam();
    printf("\n\n******** test mkdtemp ********\n");
    _test_mkdtemp();
    M_TRACE("---------  End test_printf_scanf()  ---------\n\n");
}
