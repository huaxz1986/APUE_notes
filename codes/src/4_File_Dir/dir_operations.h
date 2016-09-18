/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是目录相关的操作函数。 包括 mkdir 函数、 rmdir 函数、
 *  opendir 函数、 readdir 函数、telldir 函数的用法。
 *
 * mkdirat 函数用法类似 mkdir 函数。 fchdir 函数用法类似 chdir 函数。
 * fdopendir 函数用法类似 opendir 函数。
 *
 */
#ifndef DIR_OPERATIONS
#define DIR_OPERATIONS
#include<sys/stat.h>
#include<dirent.h>

/*!
 * \brief My_mkdir ：包装了 mkdir 函数
 * \param pathname : 传递给 mkdir 函数的 pathname 参数
 * \param mode : 传递给 mkdir 函数的 mode 参数
 * \return  : 返回 mkdir 的返回值
 */
int My_mkdir(const char*pathname,mode_t mode);
/*!
 * \brief My_rmdir ：包装了  rmdir 函数
 * \param pathname : 传递给 rmdir 函数的 pathname 参数
 * \return  : 返回 rmdir 的返回值
 */
int My_rmdir(const char *pathname);
/*!
 * \brief My_opendir ：包装了  opendir 函数
 * \param pathname : 传递给 opendir 函数的 pathname 参数
 * \return : 返回 opendir 的返回值
 */
DIR *   My_opendir(const char *pathname);
/*!
 * \brief My_readdir ：包装了  readdir 函数
 * \param dp : 传递给 readdir 函数的 dp 参数
 * \return : 返回 readdir 的返回值
 */
struct dirent * My_readdir(DIR *dp);
/*!
 * \brief My_telldir ：包装了 telldir 函数
 * \param dp : 传递给 telldir 函数的 dp 参数
 * \return : 返回 telldir 的返回值
 */
long My_telldir(DIR *dp);
/*!
 * \brief chdir ：包装了 chdir 函数
 * \param pathname : 传递给 chdir 函数的 pathname 参数
 * \return : 返回 chdir 的返回值
 */
int My_chdir(const char *pathname);
/*!
 * \brief getcwd ：包装了 getcwd 函数
 * \param buf : 传递给 getcwd 函数的 buf 参数
 * \param size : 传递给 getcwd 函数的 size 参数
 * \return : 返回 getcwd 的返回值
 */
char *My_getcwd(char *buf,size_t size);

/*!
 * \brief print_dir : 打印目录内容（递归性的）
 * \param pathname : 目录名
 */
void print_dir(const char *pathname);
/*!
 * \brief print_cwd : 打印当前工作目录
 */
void print_cwd();
/*!
 * \brief test_dir_operations : 测试目录函数
 */
void test_dir_operations();
#endif // DIR_OPERATIONS

