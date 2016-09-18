/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 fwide 函数、setvbuf 函数、 fflush函数、fopen函数 的用法。
 * freopen 函数、 fdopen 函数的用法类似 fopen 函数。
 *
 */
#ifndef FOPEN_FCLOSE
#define FOPEN_FCLOSE
#include<stdio.h>

/*!
 * \brief My_fwide : 包装了 fwide 函数
 * \param fp : 传递给 fwide 函数的 fp 参数
 * \param mode : 传递给 fwide 函数的 mode 参数
 * \return : 返回 fwide 函数的值
 */
int My_fwide(FILE *fp,int mode);

/*!
 * \brief My_setvbuf : 包装了 setvbuf 函数
 * \param fp : 传递给 setvbuf 函数的 size 参数
 * \param buf : 传递给 setvbuf 函数的 size 参数
 * \param mode : 传递给 setvbuf 函数的 size 参数
 * \param size : 传递给 setvbuf 函数的 size 参数
 * \return : 返回 setvbuf 函数的值
 */
int My_setvbuf(FILE * fp,char*  buf,int mode,size_t size);
/*!
 * \brief My_fflush : 包装了 fflush 函数
 * \param fp : 传递给 fflush 函数的 fp 参数
 * \return : 返回 fflush 函数的值
 */
int My_fflush(FILE *fp);
/*!
 * \brief My_fopen : 包装了 fopen 函数
 * \param pathname : 传递给 fopen 函数的 pathname 参数
 * \param type : 传递给 fopen 函数的 type 参数
 * \return  : 返回 fopen 函数的值
 */
FILE * My_fopen(const char* pathname,const char* type);

/*!
 * \brief set_no_buf : 设置不带缓冲
 * \param fp : 被设置的文件指针
 */
void set_no_buf(FILE *fp);
/*!
 * \brief set_line_buf : 设置行缓冲
 * \param fp : 被设置的文件指针
 */
void set_line_buf(FILE *fp);
/*!
 * \brief set_full_buf : 设置全缓冲
 * \param fp : 被设置的文件指针
 */
void set_full_buf(FILE *fp);
/*!
 * \brief print_FILE : 打印 FILE 结构
 * \param fp : 指向 FILE 的指针
 */
void print_FILE(const FILE *fp);
/*!
 * \brief test_fopen_fwide_setvbuf : 测试 fopen函数、 fwide 函数、setvbuf函数、 fflush函数的用法
 */
void test_fopen_fwide_setvbuf();
#endif // FOPEN_FCLOSE

