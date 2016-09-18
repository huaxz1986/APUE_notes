/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 fmemopen 函数的用法。
 * open_memstream 函数、 open_wmemstream 函数的用法类似 fmemopen 函数。
 *
 */
#include"../header.h"
#include"fmemopen_.h"

extern char * My_fgets(char *buf, int n, FILE *fp);
extern int My_fputs(const char *str, FILE *fp);
extern off_t My_ftello(FILE *fp);
extern int My_fseeko(FILE *fp,off_t offset,int whence);

FILE *My_fmemopen(void *buf, size_t size, const char *type)
{
    FILE *file=fmemopen(buf,size,type);
    if(NULL==file)
        printf("memopen(%p,%d,\"%s\") failed ,because %s\n",
               buf,size,type,strerror(errno));
    else printf("memopen(%p,%d,\"%s\") ok\n",buf,size,type);
    return file;
}

void test_memstream()
{
    M_TRACE("---------  Begin test_memstream()  ---------\n");
    char mem_buffer[16];
    FILE *fp=My_fmemopen(mem_buffer,16,"r+");
    if(NULL!=fp)
    {

        char read_write_buffer[8];
        My_ftello(fp);   // 查看当前位置
        //**** 写入 ****//
        My_fputs("abcdefg\n",fp); // 每次7个字符加一个换行符
        My_fputs("0123456789",fp); // 没有换行符
        My_ftello(fp);   // 查看当前位置
        fflush(fp);
        print_char_buffer(mem_buffer,16);
        //**** 读取 ****//
        My_fseeko(fp,0,SEEK_SET); //重定位到文件头
        My_ftello(fp); // 查看当前位置
        My_fgets(read_write_buffer,8,fp); // 读取 abcdefg
        My_fgets(read_write_buffer,8,fp); // 读取 \n
        My_fgets(read_write_buffer,8,fp);// 读取 0123456，文件指针指向 null 字节
        My_fgets(read_write_buffer,8,fp);// 遇到 EOF，即 null 字节 （最后一个字节为 null 字节，因此有效字节只有15个字节）
        My_ftello(fp); // 查看当前位置，文件指针指向最后一个字节的下一个字节
        My_fgets(read_write_buffer,8,fp);// 遇到 EOF，此时读取返回 EOF，并且是 ferror 返回真，且 feof 返回真
        printf("feof=%d,ferror=%d\n",feof(fp),ferror(fp)); //ferror 返回真，且 feof 返回真

        print_char_buffer(mem_buffer,16); // 读取并不会删除 mem_buffer 中的内容
        fclose(fp);
    }
    M_TRACE("---------  End test_memstream()  ---------\n\n");
}
