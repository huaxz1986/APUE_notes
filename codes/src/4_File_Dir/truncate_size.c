/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 truncate 函数的用法。 ftruncate 函数用法类似 truncate 函数用法
 *
 */
#include"../header.h"
#include"truncate_size.h"
#include<fcntl.h>
#include<unistd.h>


extern int My_open(const char *path, int oflag);
extern void print_file_size(const char *pathname);

int My_truncate(const char *pathname, off_t length)
{
    int result=truncate(pathname,length);
    if(-1==result)
        printf("truncate(\"%s\",%d) failed,because %s\n",pathname,length,strerror(errno));
    else
    {
        printf("truncate(\"%s\",%d) ok\n",pathname,length);
        print_file_size(pathname);
    }
    return result;
}
void truncate_and_read(const char *pathname,int fd,off_t length)
{
    char buffer[100];
    int len;
    My_truncate(pathname,length);
    My_lseek(fd,0,SEEK_SET);  // 读取之前先调整文件读取位置
    len=My_read(fd,buffer,length);
    printf("Read:");
    for (int i=0;i<len;i++)  // 打印读取内容
        printf("\t0x%x,",buffer[i]);
    printf("\n");
}

void test_truncate_size()
{
    M_TRACE("---------  Begin test_truncate_size()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);

    int fd=My_open("test",O_RDWR);
    My_write(fd,"abcdefg",8);
    print_file_size("test");  // 打印文件大小
    truncate_and_read("test",fd,20); // 扩张文件
    truncate_and_read("test",fd,5); // 截断文件
    close(fd);

    un_prepare_file("test");
    M_TRACE("---------  End test_truncate_size()  ---------\n");
}
