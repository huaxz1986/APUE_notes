/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十章：信号
 *
 * 测试 sigsetjmp 函数、 siglongjmp 函数的用法
 *
 */
#include"sigsetjmp_siglongjmp.h"
#include"../header.h"
#include<signal.h>

typedef void Hanlder_Func (int signo,siginfo_t *info, void *context);
extern void print_sigset(const sigset_t *set);
extern void print_progress_pending_sigset();
extern void print_progress_mask_sigset();
extern void add_sigaction(int signo,sigset_t *set,int no_deffer,int restart,Hanlder_Func handler);

static sigjmp_buf env;
/*!
 * \brief sig_print : 信号处理函数
 * \param signo : 信号值
 * \param info : 指向 siginfo_t 的指针
 * \param context : 指向 ucontext_t * 的指针
 */
static void sig_print(int signo,siginfo_t *info, void *context)
{
    printf("------ Begin signal Hanlder<signo=%s> ------\n\n",strsignal(signo));
    psiginfo(info,"The siginfo is:\t");
    printf("------ End signal Hanlder<signo=%s> ------\n\n",strsignal(signo));
    siglongjmp(env,signo);
}

void print_sigjmp_buf(const sigjmp_buf env)
{
    printf("sigjmp_buf is:\n");
    printf("\t data is:");
    for(int i=0;i<8;i++)
    {
       printf("%d,",env[0].__jmpbuf[i]);
    }
    printf("\n");
    printf("\tmask_was_saved is %d\n",env[0].__mask_was_saved);
    printf("\tsaved sigset mask is:");
    print_sigset(&env[0].__saved_mask);

}

void test_sigsetjmp_siglongjmp()
{
    M_TRACE("---------  Begin test_setjmp_longjmp()  ---------\n");
    print_progress_mask_sigset(); //打印当前的信号屏蔽字

    add_sigaction(SIGINT,NULL,0,1,sig_print);
    add_sigaction(SIGALRM,NULL,0,1,sig_print);


    int jmpval=sigsetjmp(env,1);
    switch (jmpval) {
        case 0://首次遇到
            raise(SIGINT);
            break;
        case SIGINT:
            printf("**** SIGINT:After siglongjmp from  signal handler**** \n");
            print_progress_mask_sigset(); //打印当前的信号屏蔽字
            raise(SIGALRM);
            break;
        case SIGALRM:
            printf("**** SIGALRM:After siglongjmp from  signal handler**** \n");
            print_progress_mask_sigset(); //打印当前的信号屏蔽字
            break;
        default:
            printf("Never happened\n");
            break;
        }
    M_TRACE("---------  End test_setjmp_longjmp()  ---------\n\n");
}
