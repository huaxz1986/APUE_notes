/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第六章：系统数据文件和信息。
 *
 * 这里是时间相关函数的测试。
 *
 */
#include"times_.h"
#include"../header.h"

time_t My_time(time_t *calptr)
{
    time_t result=time(calptr);

    if(-1==result)
        printf("time(%p) failed,because %s\n",calptr,strerror(errno));
    else
    {
        printf("time(%p) ok:",calptr);
        print_time_t(result);
    }
    return result;
}
int My_clock_gettime(clockid_t clock_id, struct timespec *tsp)
{
    int result=clock_gettime(clock_id,tsp);
    if(-1==result)
    {
        printf("clock_gettime(%d,%p) failed,because %s\n",clock_id,tsp,strerror(errno));
    }else
    {
        printf("clock_gettime(%d,%p) ok:",clock_id,tsp);
        print_timespec(tsp);
    }
    return result;
}
int My_clock_getres(clockid_t clock_id, struct timespec *tsp)
{
    int result=clock_getres(clock_id,tsp);
    if(-1==result)
    {
        printf("clock_getres(%d,%p) failed,because %s\n",
               clock_id,tsp,strerror(errno));
    }else
    {
        printf("clock_getres(%d,%p) ok:",clock_id,tsp);
        print_timespec(tsp);
    }
    return result;
}
int My_clock_settime(clockid_t clock_id,const struct timepsec *tsp)
{
    int result=clock_settime(clock_id,tsp);
    if(-1==result)
    {
        printf("clock_settime(%d,%p) failed,because %s\n",
               clock_id,tsp,strerror(errno));
    }else
    {
        printf("clock_settime(%d,%p) ok\n",clock_id,tsp);
    }
    return result;
}
int My_gettimeofday(struct timeval *tp, void *tzp)
{
    gettimeofday(tp,tzp);
    print_timeval(tp);
    return 0;// 总是返回 0
}
struct tm* My_gmtime(const time_t *calptr)
{
    struct tm*result=gmtime(calptr);
    if(NULL==result)
    {
        printf("gmtime(%p) failed ,because %s\n",
               calptr,strerror(errno));
    }else
    {
        printf("gmtime(%p) ok:",calptr);
        print_tm(result);
    }
    return result;
}
struct tm* My_localtime(const time_t *calptr)
{
    struct tm*result=localtime(calptr);
    if(NULL==result)
    {
        printf("localtime(%p) failed ,because %s\n",
               calptr,strerror(errno));
    }else
    {
        printf("localtime(%p) ok:",calptr);
        print_tm(result);
    }
    return result;
}
time_t My_mktime(struct tm *tmptr)
{
    time_t result=mktime(tmptr);
    if(-1==result)
    {
        printf("mktime(%p) failed,because %s\n",
               tmptr,strerror(errno));
    }else
    {
        printf("mktime(%p) ok:",tmptr);
        print_time_t(result);
    }
    return result;
}
void print_time_t(const time_t tm_t)
{
    struct tm *gtm=gmtime(&tm_t);
    char buffer[128];
    strftime(buffer,128,"%F  %T\n",gtm);
    printf("%s\n",buffer);
}
void print_tm(const struct tm *tm_tm)
{
    if(tm_tm==NULL)
    {
        printf("NULL\n");
        return;
    }
    time_t tm_t=mktime(tm_tm);
    if(-1==tm_t)
        return;

    struct tm *gtm=gmtime(&tm_t);
    char buffer[128];
    strftime(buffer,128,"%F  %T\n",gtm);
    printf("%s\n",buffer);
}
void print_timeval(const struct timeval *tm_val)
{
    if(tm_val==NULL)
    {
        printf("NULL\n");
        return;
    }
    time_t t_tm=tm_val->tv_sec;
    struct tm *gtm=gmtime(&t_tm);
    char buffer[128];
    strftime(buffer,128,"%F  %T",gtm);
    printf("%s <us:%d>\n",buffer,tm_val->tv_usec);
}
void print_timespec(const struct timespec *tm_tsp)
{
    if(tm_tsp==NULL)
    {
        printf("NULL\n");
        return;
    }
    time_t t_tm=tm_tsp->tv_sec;
    struct tm *gtm=gmtime(&t_tm);
    char buffer[128];
    strftime(buffer,128,"%F  %T",gtm);
    printf("%s <ns:%d>\n",buffer,tm_tsp->tv_nsec);
}
void test_times()
{
    M_TRACE("---------  Begin test_times()  ---------\n");
    struct timespec tsp_time;
    struct timeval tvl_time;
    time_t tm_t;

    My_time(NULL);

    printf("\n\n******** test clock_gettime *********\n");
    My_clock_gettime(CLOCK_REALTIME,&tsp_time);
    My_clock_gettime(CLOCK_MONOTONIC,&tsp_time);
    My_clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tsp_time);
    My_clock_gettime(CLOCK_THREAD_CPUTIME_ID,&tsp_time);
    printf("\n\n******** test clock_getres  *********\n");
    tsp_time.tv_sec=time(NULL);  //重新设定为当前时间
    My_clock_getres(CLOCK_REALTIME,&tsp_time); //获取始终精度，只有 ns 单位才有意义
    My_clock_getres(CLOCK_MONOTONIC,&tsp_time); //获取始终精度，只有 ns 单位才有意义
    My_clock_getres(CLOCK_PROCESS_CPUTIME_ID,&tsp_time); //获取始终精度，只有 ns 单位才有意义
    My_clock_getres(CLOCK_THREAD_CPUTIME_ID,&tsp_time); //获取始终精度，只有 ns 单位才有意义
    printf("\n\n******** test clock_settime *********\n");
    tsp_time.tv_sec=time(NULL);  //重新设定为当前时间
    My_clock_settime(CLOCK_REALTIME,&tsp_time);
    My_clock_settime(CLOCK_MONOTONIC,&tsp_time);
    My_clock_settime(CLOCK_PROCESS_CPUTIME_ID,&tsp_time);
    My_clock_settime(CLOCK_THREAD_CPUTIME_ID,&tsp_time);
    printf("\n\n");
    My_gettimeofday(&tvl_time,NULL);
    tm_t=time(NULL); // 初始化 tm_t
    struct tm * tm_tm=My_gmtime(&tm_t);
    My_localtime(&tm_t);
    My_mktime(tm_tm);
    M_TRACE("---------  End test_times()  ---------\n\n");
}
