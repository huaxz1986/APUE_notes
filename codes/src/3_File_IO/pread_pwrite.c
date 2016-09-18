/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 * 这里是 pread函数、pwrite 函数的用法
 *
 */
#include"pread_pwrite.h"
#include<fcntl.h>
#include<stdio.h>
extern int My_open(const char *path, int oflag);

ssize_t My_pread(int fd, void *buf, size_t nbytes, off_t offset)
{
    ssize_t result=pread(fd,buf,nbytes,offset);
    if(-1==result)
        printf("pread(%d,%p,%d,%d) failed,because %s\n",fd,buf,nbytes,offset,strerror(errno));
    else
        printf("pread(%d,%p,%d,%d) %d bytes,after that:\t",fd,buf,nbytes,offset,result);
    return result;
}

ssize_t My_pwrite(int fd,const void*buf,size_t nbytes,off_t offset)
{
    ssize_t result=pwrite(fd,buf,nbytes,offset);
    if(-1==result)
        printf("pwrite(%d,%p,%d,%d) failed,because %s\n",fd,buf,nbytes,offset,strerror(errno));
    else
        printf("pwrite(%d,%p,%d,%d) %d bytes,after that:\t",fd,buf,nbytes,offset,result);
    return result;
}

void test_pread_pwrite()
{
    M_TRACE("---------  Begin test_pread_pwrite()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);


    int fd=My_open("test",O_RDWR|O_TRUNC);  // 读写打开，并截断
    if(-1==fd)  return; // 文件打开失败
    char read_buffer[20];
    char write_buffer[20];
    strcpy(write_buffer,"123456789"); // write_buffer 填充数字

    // 写文件，期望写 10 个字节
    My_write(fd,write_buffer,10);
    print_current_offset(fd);
    My_pread(fd,read_buffer,5,0 );// 读文件，期望读  5 个字节,从 偏移为 0 开始
    print_current_offset(fd);
    My_pwrite(fd,write_buffer,10,8);// 写文件，期望写 10 个字节，从 偏移为 8 开始
    print_current_offset(fd);
    close(fd);

    un_prepare_file("test");
    M_TRACE("---------  End test_pread_pwrite()  ---------\n\n");
}

void print_current_offset(int fd)
{
    off_t off= My_lseek(fd,0,SEEK_CUR);
    if(-1==off) return; // lseek 失败
    printf("The current offset is %d\n",off);
}
