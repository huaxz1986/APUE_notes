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
#ifndef LSEEK_READ_WRITE
#define LSEEK_READ_WRITE
#include"../header.h"
#include<unistd.h>
#include"open_creat.h"

/*!
 * \brief My_lseek :包装了 lseek 函数
 * \param fd : 传递给 lseek 函数的 fd 参数
 * \param offset : 传递给 lseek 函数的 offset 参数
 * \param whence : 传递给 lseek 函数的 whence 参数
 * \return ： 返回 lseek 函数的值
 */
off_t My_lseek(int fd, off_t offset,int whence);
/*!
 * \brief My_read : 包装了 read 函数
 * \param fd : 传递给 read 函数的 fd 参数
 * \param buf : 传递给 read 函数的 buf 参数
 * \param nbytes : 传递给 read 函数的 nbytes 参数
 * \return ： 返回 read 函数的值
 */
ssize_t My_read(int fd,void *buf,size_t nbytes);
/*!
 * \brief My_write  : 包装了 write 函数
 * \param fd  : 传递给 write 函数的 fd 参数
 * \param buf : 传递给 write 函数的 buf 参数
 * \param nbytes  : 传递给 write 函数的 nbytes 参数
 * \return  ： 返回 write 函数的值
 */
ssize_t My_write(int fd,const void *buf,size_t nbytes);



/*!
 * \brief test_lseek_read_write ： 测试 lseek、read、write 函数
 */
void test_lseek_read_write();




#endif // LSEEK_READ_WRITE

