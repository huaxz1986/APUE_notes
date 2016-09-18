/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第三章：文件IO：不带缓冲的IO。
 *
 * 这里是 fcntl 函数的用法
 *
 */
#ifndef FCNTL_
#define FCNTL_

/*!
 * \brief My_fcntl_DUPFD :  包装了 fcntl 函数：fcntl 之复制文件描述符命令（ F_DUPFD)
 * \param fd : 待复制的文件描述符
 * \param arg : 新的文件描述符是尚未打开的文件描述符中大于或等于arg 中的最小值
 * \return ： 成功：一个新的文件描述符，其中 FD_CLOEXEC 标志被清除；失败： -1
 */
int My_fcntl_DUPFD(int fd,int arg);
/*!
 * \brief My_fcntl_DUPFD_CLOEXEC :  包装了 fcntl 函数：fcntl 之复制文件描述符命令（ F_DUPFD_CLOEXEC )
 * \param fd : 待复制的文件描述符
 * \param arg : 新的文件描述符是尚未打开的文件描述符中大于或等于arg 中的最小值
 * \return ： 成功：一个新的文件描述符，其中 FD_CLOEXEC 标志被设置；失败： -1
 */
int My_fcntl_DUPFD_CLOEXEC(int fd,int arg);
/*!
 * \brief My_fcntl_GETFD :   包装了 fcntl 函数： fcntl 之获取文件描述符标志命令（ F_GETFD)
 * \param fd : 待获取的文件描述符
 * \return ： 成功：文件描述符的标志（目前仅有 FD_CLOEXE 标志）；失败： -1
 */
int My_fcntl_GETFD(int fd);
/*!
 * \brief My_fcntl_SETFD  :    包装了 fcntl 函数：fcntl 之设置文件描述符标志命令（ F_GETFD)
 * \param fd : 待设置的文件描述符
 * \param arg ： 文件描述符的标志（目前仅有 FD_CLOEXE 标志）
 * \return ： 成功： 返回非 -1； 失败： 返回 -1
 */
int My_fcntl_SETFD(int fd,int arg);
/*!
 * \brief My_fcntl_GETFL :   包装了 fcntl 函数： fcntl 之获取文件状态标志命令（ F_GETFL)
 * \param fd : 待获取的文件描述符
 * \return : 成功：文件状态标志（如读写方式、阻塞方式、同步方式等）；失败： 返回 -1
 */
int My_fcntl_GETFL(int fd);
/*!
 * \brief My_fcntl_SETFL :   包装了 fcntl 函数： fcntl 之设置文件状态标志命令（ F_GETFL)
 * \param fd : 待设置的文件描述符
 * \param arg ： 文件状态标志
 * \return ： 成功： 返回非 -1； 失败： 返回 -1
 */
int My_fcntl_SETFL(int fd,int arg);
/*!
 * \brief My_fcntl_GETOWN :  包装了 fcntl 函数： fcntl 之获取接收`SIGIO`和`SIGURG`信号进程命令 (F_GETOWN)
 * \param fd : 待获取的文件描述符
 * \return ： 成功：接收`SIGIO`和`SIGURG`信号的进程或者进程组 ； 失败： 返回 -1
 */
int My_fcntl_GETOWN(int fd);
/*!
 * \brief My_fcntl_SETOWN :   包装了 fcntl 函数：fcntl 之设置接收`SIGIO`和`SIGURG`信号进程命令 (F_GETOWN)
 * \param fd :  待设置的文件描述符
 * \param arg : 如果是正数，则设定进程 ID；如果是负数，则设定进程组 ID
 * \return : 成功：返回非 -1 ； 失败 ： 返回 -1
 */
int My_fcntl_SETOWN(int fd,int arg);

/*!
 * \brief print_fl : 打印文件描述符 fd 的文件状态标志
 * \param fd : 文件描述符
 * \param flag : 文件状态标志
 */
void print_fl(int fd,int flag);

/*!
 * \brief test_fcntl : 测试 fcntl 函数
 */
void test_fcntl();

#endif // FCNTL_

