/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 getpgrp 函数、getpgid 函数的用法
 *
 */
#ifndef GETPGRP_GETPGID
#define GETPGRP_GETPGID
#include<unistd.h>

/*!
 * \brief My_getpgrp :  包装了 getpgrp 函数
 * \return  : 返回 getpgrp 函数的值
 */
pid_t My_getpgrp(void);
/*!
 * \brief My_getpgid :  包装了 getpgid 函数
 * \param pid : 传递给 getpgid 函数的 pid 参数
 * \return  : 返回 getpgid 函数的值
 */
pid_t My_getpgid(pid_t pid);

/*!
 * \brief test_getpgrp_getpgid :测试 getpgrp 函数、getpgid 函数的用法
 */
void test_getpgrp_getpgid();
#endif // GETPGRP_GETPGID

