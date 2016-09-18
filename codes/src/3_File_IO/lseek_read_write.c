/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 * 这里是 lseek函数、read函数、write函数的用法
 *
 */
#include<stdio.h>
#include<fcntl.h>
#include"../header.h"

extern int My_open(const char *path, int oflag);


off_t My_lseek(int fd, off_t offset,int whence)
{
    off_t result=lseek(fd,offset,whence);
    if(-1==result)
        printf("lseek(%d,%d,%d) failed,because %s\n",fd,offset,whence,strerror(errno));
    else
        printf("lseek(%d,%d,%d) to offset %d\n",fd,offset,SEEK_SET,result);
    return result;
}
ssize_t My_read(int fd,void *buf,size_t nbytes)
{
    ssize_t result=read(fd,buf,nbytes);
    if(-1==result)
        printf("read(%d,%p,%d) failed,because %s\n",fd,buf,nbytes,strerror(errno));
    else
        printf("read(%d,%p,%d) %d bytes\n",fd,buf,nbytes,result);
    return result;
}
ssize_t My_write(int fd,const void *buf,size_t nbytes)
{
    ssize_t result=write(fd,buf,nbytes);
    if(-1==result)
        printf("write(%d,%p,%d) failed,because %s\n",fd,buf,nbytes,strerror(errno));
    else
        printf("write(%d,%p,%d) %d bytes\n",fd,buf,nbytes,result);
    return result;
}

void test_lseek_read_write()
{
    M_TRACE("---------  Begin test_lseek_read_write()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);

    int fd=My_open_with_mode("test",O_RDWR|O_TRUNC);  // 读写打开，并截断
    if(-1==fd)  return; // 文件打开失败
    char read_buffer[20];
    char write_buffer[10];

    strcpy(write_buffer,"123456789"); // write_buffer 填充数字

    My_read(fd,read_buffer,20); // 读文件，期望读 20 个字节
    My_write(fd,write_buffer,10);// 写文件，期望写 10 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_lseek(fd,0,SEEK_SET);// 定位文件到头部
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_lseek(fd,10,SEEK_END);// 定位文件到尾部之后的 10 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_write(fd,write_buffer,10);// 写文件，期望写 10 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_lseek(fd,0,SEEK_SET);// 定位文件到头部
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    close(fd);

    un_prepare_file("test");
    M_TRACE("---------  End test_lseek_read_write()  ---------\n\n");

}
