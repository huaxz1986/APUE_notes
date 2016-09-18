/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   tools 头文件。
 *
 * 主要是定义了一些工具函数
 *
 */
#ifndef TOOLS
#define TOOLS
#include <sys/types.h>
#include<time.h>
#include<fcntl.h>
/*!
 * \brief prepare_file : 为测试准备条件：新建一个文件（若存在则先删除之），然后向文件中写入指定内容
 * \param pathname : 新建的文件的路径名（若存在则先删除之）
 * \param buffer : 待写入文件的内容缓冲区
 * \param len : 待写入文件的内容的长度
 * \param mode ： 新建文件的权限
 */
int prepare_file(const char*pathname,const void *buffer,int len,mode_t mode);
/*!
 * \brief un_prepare_file : 清理测试准备条件：删除新建的文件
 * \param pathname : 新建的文件的路径名
 */
void un_prepare_file(const char *pathname);


/*!
 * \brief print_char_buffer : 打印字符数组的内容
 * \param buf : 数组地址
 * \param n : 数组长度
 */
void print_char_buffer(const char*buf,int n);
/*!
 * \brief fcntl_lock : 使用 fcntl 记录锁加锁
 * \param fd : 加锁的文件的文件描述符
 */
void fcntl_lock(int fd);
/*!
 * \brief fcntl_unlock : 解锁 fcntl 记录锁
 * \param fd : 解锁的文件的文件描述符
 */
void fcntl_unlock(int fd);

/*!
 * \brief cur_abs_path : 根据目录和相对目录的文件名拼接绝对路径名
 * \param dir_name : 目录的绝对路径名
 * \param file_name : 文件名
 * \return : 该文件名的绝对路径名字符串的地址（静态数组存放）
 */
char* abs_path(const char*dir_name,const char* file_name);

#endif // TOOLS

