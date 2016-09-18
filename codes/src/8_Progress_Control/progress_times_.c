/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第八章：进程环境
 *
 * 测试 times 函数的用法 （它用于获取进程以及已经终止子进程的运行时间）
 *
 */

#include"progress_times_.h"
#include"../header.h"
#include<unistd.h>
extern void print_pid();
extern void print_parent_pid();
extern void check_waitpid();

clock_t My_times(struct tms *buf)
{
    clock_t result=times(buf);
    if(-1==result)
    {
        printf("times(%p) failed,because %s\n",
               buf,strerror(errno));
    }else
    {
        printf("times(%p) ok:",buf);
        print_struct_tms(buf);
    }
    return result;
}
long clock_2_second(clock_t clk)
{
    return clk/sysconf(_SC_CLK_TCK);
}
void print_struct_tms(const struct tms*tm)
{
    printf("struct tms is:\n");
    if(tm==NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("\tuser cpu time:%d clock(=%d s)\n"
           ,tm->tms_utime,clock_2_second(tm->tms_utime));
    printf("\tsystem cpu time:%d clock(=%d s)\n"
           ,tm->tms_stime,clock_2_second(tm->tms_stime));
    printf("\tchilds user cpu time:%d clock(=%d s)\n"
           ,tm->tms_cutime,clock_2_second(tm->tms_cutime));
    printf("\tchilds system cpu time:%d clock(=%d s)\n",
           tm->tms_cstime,clock_2_second(tm->tms_cstime));
}

/*!
 * \brief busy_work : 用 for 循环模拟 CPU 繁忙的计算任务
 * \param iterate_num : for 循环的次数
 */
static void busy_work(long iterate_num)
{
    long num;
    for(int i=0;i<iterate_num;i++) //累加
                 num+=i%7;
}
/*!
 * \brief create_child : 创建子进程
 * \param fd : 用于记录锁的文件描述符
 * \param iterate_num : for 迭代数量
 * \return : fork 的返回值
 */
static pid_t create_child(int fd,long iterate_num)
{
    pid_t pid=fork();
    if(0==pid)
    {// child
        fcntl_lock(fd);  // 加锁
        printf("************ In Child **********\n");
        print_pid();
        print_parent_pid();
        clock_t t1,t2; // 用于获取时间跨度
        struct tms buf;
        t1=My_times(&buf);
        sleep(2); //睡眠2秒
        busy_work(iterate_num);
        t2=My_times(&buf);
        printf("Child elapsed time is %d s\n",clock_2_second(t2-t1));
        printf("************ In Child **********\n");
        fcntl_unlock(fd); // 解锁
        _exit(0); //_exit 退出
    }
    return pid;
}



void test_progress_times()
{
    M_TRACE("---------  Begin test_progress_times()  ---------\n");
    assert(prepare_file("test","abc",3,S_IRWXU)==0);
    int fd=My_open("test",O_RDWR);
    if(-1==fd)
    {
        un_prepare_file("test");
        M_TRACE("---------  End test_fork()  ---------\n\n");
        return;
    }
    //****** 打开文件成功 *************//
    clock_t t1,t2;
    struct tms buf;
    t1=times(&buf);
    create_child(fd,1000000000);// 子进程直接 _exit
    create_child(fd,2000000000);// 子进程直接 _exit
    sleep(5);// 让子进程获得锁，否则父进程持有锁，然后等待子进程结束，最后死锁
    fcntl_lock(fd);  // 加锁
    busy_work(1000000000);// 只有父进程能到达这里
    check_waitpid();
    t2=My_times(&buf);
    printf("Parent elapsed time is %d s\n",clock_2_second(t2-t1));\
    fcntl_unlock(fd); // 解锁

    close(fd);
    un_prepare_file("test");
    M_TRACE("---------  End test_progress_times()  ---------\n\n");
}
