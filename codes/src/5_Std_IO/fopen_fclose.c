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
#include"fopen_fclose.h"
#include"../header.h"
#include<fcntl.h>
#include<wchar.h>


int My_fwide(FILE *fp, int mode)
{
    if(NULL==fp) return 0;
    int result=fwide(fp,mode);
    if(result>0)
        printf("fp(%p) is wide-byte-flow\n",fp);
    else if(result <0)
        printf("fp(%p) is byte-flow\n",fp);
    else
        printf("fp(%p) is unordered\n",fp);
    return result; // 没有失败的情况
}
int My_setvbuf(FILE *fp, char *buf, int mode, size_t size)
{
    int result=setvbuf(fp,buf,mode,size);
    if(0!=result) // 失败返回非 0
        printf("setvbuf(%p,%p,%d,%d) failed,because %s\n",fp,buf,mode,size,strerror(errno));
    else
        printf("setvbuf(%p,%p,%d,%d) ok\n",fp,buf,mode,size);
    return result;
}
int My_fflush(FILE *fp)
{
    int result=fflush(fp);
    if(EOF==result) //失败返回 EOF 而不是 -1
    {
        printf("fflush(%p) failed,because %s\n",fp,strerror(errno));
    }else
        printf("fflush(%p) ok\n",fp);
    return result;
}
FILE * My_fopen(const char *pathname, const char *type)
{
    FILE *file=fopen(pathname,type);
    if(NULL==file)
    {
        printf("open(\"%s\",\"%s\") failed,because %s\n",pathname,type,strerror(errno));
    }else
    {
        printf("open(\"%s\",\"%s\") ok\n",pathname,type);
    }
    return file;
}
void set_no_buf(FILE *fp)
{
   int result=setvbuf(fp,NULL,_IONBF,0);
   if(0!=result)// 失败返回非 0
       printf("set_no_buf(%p) failed,because %s\n",fp,strerror(errno));
   else
       printf("set_no_buf(%p) ok\n",fp);
}
void set_line_buf(FILE *fp)
{
    int result=setvbuf(fp,NULL,_IOLBF,0);
    if(0!=result)// 失败返回非 0
        printf("set_line_buf(%p) failed,because %s\n",fp,strerror(errno));
    else
        printf("set_line_buf(%p) ok\n",fp);
}
void set_full_buf(FILE *fp)
{
    int result=setvbuf(fp,NULL,_IOFBF,0);
    if(0!=result)// 失败返回非 0
        printf("set_full_buf(%p) failed,because %s\n",fp,strerror(errno));
    else
        printf("set_full_buf(%p) ok\n",fp);
}
void print_FILE(const FILE *fp)
{
    printf("FILE %p is :",fp);
    if(NULL==fp)
    {
        printf("NULL\n");
        return;
    }
    printf("\tfile descriptor is :%d\n",fp->_fileno);
    printf("\tbuffer address is :0x%x\n",fp->_IO_buf_base);
    printf("\tbuffer length is :%d\n",fp->_IO_buf_end-fp->_IO_buf_base);
    printf("\tFILE status is :0x%x\n",fp->_flags);
}

void test_fopen_fwide_setvbuf()
{
    M_TRACE("---------  Begin test_fopen_fwide_setvbuf()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);


    My_fwide(stdin,0); //打印 stdin 的流向
    My_fwide(stdout,0); //打印 stdout 的流向
    My_fwide(stderr,0); //打印 stderr 的流向
    print_FILE(stdin); //打印 stdin 结构
    print_FILE(stdout); //打印 stdout 结构
    print_FILE(stderr); //打印 stderr 结构

    FILE *fp=My_fopen("test","r+");
    if(NULL!=fp)
    {
        My_fwide(fp,0); //打印 fp 的流向
        My_fwide(fp,-1); //设置 fp 为字节流 然后打印 fp 的流向
        My_fwide(fp,1); //无法修改已定向的流
        print_FILE(fp);
        //**** 设置不同的缓冲 ****//
        set_full_buf(fp);
        print_FILE(fp);
        set_line_buf(fp);
        print_FILE(fp);
        set_no_buf(fp);
        print_FILE(fp);

        fclose(fp); //关闭流
    }
    un_prepare_file("test");
    M_TRACE("---------  End test_fopen_fwide_setvbuf()  ---------\n\n");
}
