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
#ifndef PREAD_PWRITE
#define PREAD_PWRITE
#include"../header.h"
#include<unistd.h>
/*!
 * \brief My_pread :  pread 函数的包装函数
 * \param fd : 传递给 pread 函数的 fd 参数
 * \param buf : 传递给 pread 函数的 buf 参数
 * \param nbytes : 传递给 pread 函数的 nbytes 参数
 * \param offset : 传递给 pread 函数的 offset 参数
 * \return : 返回 pread 函数的值
 */
ssize_t My_pread(int fd,void*buf,size_t nbytes,off_t offset);
/*!
 * \brief My_pwrite :  pwrite 函数的包装函数
 * \param fd : 传递给 pwrite 函数的 fd 参数
 * \param buf : 传递给 pwrite 函数的 buf 参数
 * \param nbytes : 传递给 pwrite 函数的 nbytes 参数
 * \param offset  : 传递给 pwrite 函数的 offset 参数
 * \return : 返回 pwrite 函数的值
 */
ssize_t My_pwrite(int fd,const void*buf,size_t nbytes,off_t offset);

/*!
 * \brief print_current_offset : 打印文件的当前偏移量
 * \param fd : 传递给 lseek 函数的 fd 参数
 */
void print_current_offset(int fd);

/*!
 * \brief test_pread_pwrite : 测试 pread、pwrite 函数
 * \param fd : 打开的文件描述符
 */
void test_pread_pwrite();
#endif // PREAD_PWRITE

