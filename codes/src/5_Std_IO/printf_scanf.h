/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第五章：标准 IO 库。
 *
 * 这里是 printf 函数、snprintf 函数、 scanf 函数、sscanf 函数 的用法。
 * fprintf 函数、 dprintf 函数的用法类似 printf 函数。
 * sprintf 函数的用法类似 snprintf 函数。
 * fscanf 函数的用法类似 scanf 函数。
 *
 *
 */
#ifndef PRINTF_SCANF
#define PRINTF_SCANF


/*!
 * \brief _test_printf : 测试 printf 函数
 */
void _test_printf();
/*!
 * \brief _test_snprintf : 测试 snprintf 函数
 */
void _test_snprintf();
/*!
 * \brief _test_scanf : 测试 scanf 函数
 */
void _test_scanf();
/*!
 * \brief _test_sscanf : 测试 sscanf 函数
 */
void _test_sscanf();
/*!
 * \brief test_printf_scanf : 测试 printf 函数、 scanf 函数 ... 等函数
 */
void test_printf_scanf();

#endif // PRINTF_SCANF

