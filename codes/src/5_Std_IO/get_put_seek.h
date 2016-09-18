/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 fgetc 函数、ferror 函数、 feof函数、ungetc函数 、
 * fputc 函数、 fgets 函数、 fputs 函数、 fread 函数、
 * fwrite 函数、 ftello 函数、 fseeko 函数的用法。
 *
 * getc 函数的用法类似 fgetc 函数。
 * putc 函数的用法类似 fputc 函数。
 * gets 函数的用法类似 fgets 函数。
 * puts 函数的用法类似 fputs 函数。
 * ftell 函数的用法类似 ftello 函数。
 * fseek 函数的用法类似 fseeko 函数。
 *
 */
#ifndef GET_PUT_SEEK
#define GET_PUT_SEEK
#include<stdio.h>
/*!
 * \brief My_fgetc : 包装了 getc 函数
 * \param fp : 传递给 getc 函数的 fp 参数
 * \return  : 返回 getc 函数的值
 */
int My_fgetc(FILE*fp);

/*!
 * \brief My_ferror : 包装了 ferror 函数
 * \param fp : 传递给 ferror 函数的 fp 参数
 * \return  : 返回 ferror 函数的值
 */
int My_ferror(FILE *fp);

/*!
 * \brief My_feof : 包装了 feof 函数
 * \param fp : 传递给 feof 函数的 fp 参数
 * \return : 返回 feof 函数的值
 */
int My_feof(FILE *fp);

/*!
 * \brief My_ungetc : 包装了 ungetc 函数
 * \param c : 传递给 ungetc 函数的 c 参数
 * \param fp : 传递给 ungetc 函数的 fp 参数
 * \return : 返回 ungetc 函数的值
 */
int My_ungetc(int c,FILE *fp);

/*!
 * \brief My_fputc : 包装了 fputc 函数
 * \param c : 传递给 fputc 函数的 c 参数
 * \param fp : 传递给 fputc 函数的 fp 参数
 * \return : 返回 fputc 函数的值
 */
int My_fputc(int c,FILE*fp);

/*!
 * \brief fgets : 包装了 fgets 函数
 * \param buf : 传递给 fgets 函数的 buf 参数
 * \param n : 传递给 fgets 函数的 n 参数
 * \param fp : 传递给 fgets 函数的 fp 参数
 * \return : 返回 fgets 函数的值
 */
char *My_fgets(char * buf,int n, FILE*  fp);

/*!
 * \brief My_fputs : 包装了 fputs 函数
 * \param str : 传递给 fputs 函数的 str 参数
 * \param fp : 传递给 fputs 函数的 fp 参数
 * \return : 返回 fputs 函数的值
 */
int My_fputs(const char*  str,FILE* fp);

/*!
 * \brief My_fread : 包装了 fread 函数
 * \param ptr : 传递给 fread 函数的 ptr 参数
 * \param size : 传递给 fread 函数的 size 参数
 * \param nobj : 传递给 fread 函数的 nobj 参数
 * \param fp : 传递给 fread 函数的 fp 参数
 * \return : 返回 fread 函数的值
 */
size_t My_fread(void *  ptr,size_t size,size_t nobj,FILE *  fp);

/*!
 * \brief My_fwrite : 包装了 fwrite 函数
 * \param ptr : 传递给 fwrite 函数的 ptr 参数
 * \param size : 传递给 fwrite 函数的 size 参数
 * \param nobj : 传递给 fwrite 函数的 nobj 参数
 * \param fp : 传递给 fwrite 函数的 fp 参数
 * \return : 返回 fwrite 函数的值
 */
size_t My_fwrite(const void*  ptr,size_t size,size_t nobj,FILE *  fp);
/*!
 * \brief My_ftello : 包装了 ftello 函数
 * \param fp : 传递给 ftello 函数的 fp 参数
 * \return : 返回 ftello 函数的值
 */
off_t My_ftello(FILE *fp);
/*!
 * \brief My_fseeko : 包装了 fseeko 函数
 * \param fp : 传递给 fseeko 函数的 fp 参数
 * \param offset : 传递给 fseeko 函数的 offset 参数
 * \param whence : 传递给 fseeko 函数的 whence 参数
 * \return : 返回 fseeko 函数的值
 */
int My_fseeko(FILE *fp,off_t offset,int whence);

/*!
 * \brief test_read_write_char : 测试读写单个字符
 * \param fp : FILE 对象指针
 */
void _test_read_write_char(FILE *fp);
/*!
 * \brief test_read_write_line : 测试读写字符串
 * \param fp : FILE 对象指针
 */
void _test_read_write_line(FILE *fp);

/*!
 * \brief test_read_write_binary : 测试读写二进制对象
 * \param fp : FILE 对象指针
 */
void _test_read_write_binary(FILE *fp);

/*!
 * \brief test_get_put_seek : 测试 fgetc 函数、 fputc 函数、 fgets 函数、 fputs 函数 ... 等函数的用法
 */
void test_get_put_seek();
#endif // GET_PUT_SEEK

