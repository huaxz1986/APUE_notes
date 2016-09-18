/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 stat 函数和 lstat 函数的用法。 fstat 函数和 fstatat 函数用法类似 stat 函数用法
 *
 */
#ifndef STAT_LSTAT
#define STAT_LSTAT
#include<sys/stat.h>

/*!
 * \brief Stat : struct stat 的别名
 */
typedef struct stat Stat;

/*!
 * \brief My_stat : 包装了 stat 函数
 * \param pathname : 传递给 stat 函数的 pathname 参数
 * \param buf : 传递给 stat 函数的 buf 参数
 * \return :  返回 stat 函数值
 */
int My_stat(const char * pathname, Stat*buf);
/*!
 * \brief My_lstat : 包装了 lstat 函数
 * \param pathname : 传递给 lstat 函数的 pathname 参数
 * \param buf : 传递给 lstat 函数的 buf 参数
 * \return :  返回 lstat 函数值
 */
int My_lstat(const char* pathname,Stat *buf);
/*!
 * \brief print_stat_type : 打印文件类型
 * \param file_stat : 文件的 struct stat 结构
 * \param file_name : 文件名
 */
void print_stat_type(const Stat* file_stat,const char* file_name);
/*!
 * \brief print_stat_owners : 打印文件的相关ID
 * \param file_stat : 文件的 struct stat 结构
 * \param file_name : 文件名
 */
void print_stat_owners(const Stat* file_stat,const char* file_name);
/*!
 * \brief print_mode_perms : 打印文件的权限
 * \param mode : mode_t 类型
 * \param file_name : 文件名
 */
void print_mode_perms(mode_t mode,const char* file_name);
/*!
 * \brief print_file_type : 打印文件类型
 * \param pathname : 文件名
 */
void print_file_type(const char*pathname);
/*!
 * \brief print_file_perm : 打印文件的权限
 * \param pathname : 文件名
 */
void print_file_perm(const char*pathname);
/*!
 * \brief print_file_owner  : 打印文件的相关ID
 * \param pathname  : 文件名
 */
void print_file_owner(const char*pathname);
/*!
 * \brief print_file_size : 打印文件大小
 * \param pathname : 文件名
 */
void print_file_size(const char *pathname);
/*!
 * \brief print_file_link_num : 打印文件硬链接数量
 * \param pathname  : 文件名
 */
void print_file_link_num(const char *pathname);
/*!
 * \brief print_file_time : 打印文件的最后访问时间、最后修改时间、 i 节点状态的最后修改时间
 * \param pathname : 文件名
 */
void print_file_time(const char *pathname);
/*!
 * \brief test_stat_lstat : 测试 stat 函数和 lstat 函数
 *
 * 其中要求 `/home/huaxz1986/APUE/main.c` 文件存在
 */
void test_stat_lstat();

/*!
 * \brief file_is_dir : 判断指定路径名是否是个目录
 * \param pathname : 文件名
 * \return  : 如果指定文件名是目录，则返回 1 ; 如果该文件名不是目录，则返回 0; 如果异常则返回 -1
 */
int file_is_dir(const char *pathname);
#endif // STAT_LSTAT

