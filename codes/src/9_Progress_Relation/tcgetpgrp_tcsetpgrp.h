/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第九章：进程关系
 *
 * 测试 tcgetpgrp 函数、tcsetpgrp 函数、tcgetsid 函数的用法
 *
 */

#ifndef TCGETPGRP_TCSETPGRP
#define TCGETPGRP_TCSETPGRP

#include<unistd.h>

/*!
 * \brief My_tcgetpgrp : 包装了 tcgetpgrp 函数
 * \param fd : 传递了 tcgetpgrp 函数的 fd 参数
 * \return : 返回了 tcgetpgrp 函数的值
 */
pid_t My_tcgetpgrp(int fd);
/*!
 * \brief My_tcsetpgrp : 包装了 tcsetpgrp 函数
 * \param fd : 传递了 tcsetpgrp 函数的 fd 参数
 * \param pgrpid : 传递了 tcsetpgrp 函数的pgrpid  参数
 * \return : 返回了 tcsetpgrp 函数的值
 */
int My_tcsetpgrp(int fd,pid_t pgrpid);
/*!
 * \brief My_tcgetsid : 包装了 tcgetsid 函数
 * \param fd : 传递了 tcgetsid 函数的 fd 参数
 * \return : 返回了 tcgetsid 函数的值
 */
pid_t My_tcgetsid(int fd);

/*!
 * \brief test_tcgetpgrp_tcsetpgrp :测试 tcgetpgrp 函数、tcsetpgrp 函数、tcgetsid 函数
 */
void test_tcgetpgrp_tcsetpgrp();
#endif // TCGETPGRP_TCSETPGRP

