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


#include"get_put_seek.h"
#include"../header.h"
#include"fcntl.h"

extern FILE * My_fopen(const char *pathname, const char *type);


static struct Struct_Data{ //测试二进制读写使用的结构体
    int int_i;
    int int_j;
};
static print_struct(struct Struct_Data* data_p)
{
    printf("struct data is:\t");
    if(NULL==data_p)
    {
        printf("NULL\n");
        return;
    }
    printf("<%d,%d>\n",data_p->int_i,data_p->int_j);
}
static print_struct_buffer(struct Struct_Data* buffer,int n)
{
    printf("struct data buffer is:");
    for(int i=0;i<n;i++)
        printf("\t<%d,%d>",buffer[i].int_i,buffer[i].int_j);
    printf("\n");
}


int My_fgetc(FILE *fp)
{
    int result=fgetc(fp);
    if(EOF==result)
    {
        if(feof(fp))
            printf("fgetc(%p) read the EOF\n",fp);
        else  if(ferror(fp))
            printf("fgetc(%p) failed,because %s\n",fp,strerror(errno));
        else
            printf("fgetc(%p) can not conme here\n",fp);
    }else
    {
        printf("fgetc(%p) ok,returns 0x%x\n",fp,result);
    }
    return result;
}
int My_ferror(FILE *fp)
{
    int result=ferror(fp);
    if(result!=0)
        printf("fp %p is error\n",fp);
    else
        printf("fp %p is no error\n",fp);
    return result;
}
int My_feof(FILE *fp)
{
    int result=feof(fp);
    if(result!=0)
        printf("fp %p is at EOF\n",fp);
    else
        printf("fp %p is not at EOF\n",fp);
    return result;
}

int My_ungetc(int c, FILE *fp)
{
    int result=ungetc(c,fp);
    if(EOF==result)
        printf("ungetc(0x%x,%p) failec,because %s\n",c,fp,strerror(errno));
    else
        printf("ungetc(0x%x,%p) ok\n",c,fp);
    return result;
}
int My_fputc(int c, FILE *fp)
{
    int result=fputc(c,fp);
    if(EOF==result)
        printf("fputc(0x%x,%p) failec,because %s\n",c,fp,strerror(errno));
    else
        printf("fputc(0x%x,%p) ok\n",c,fp);
    return result;
}
char * My_fgets(char *buf, int n, FILE *fp)
{
    char *result=fgets(buf,n,fp);
    if(NULL==result)
    {
        if(feof(fp))
            printf("fgets(%p,%d,%p) read the EOF\n",buf,n,fp);
        else if(ferror(fp))
            printf("fgets(%p,%d,%p) failed,because %s\n",buf,n,fp,strerror(errno));
        else
            printf("fgets(%p,%d,%p) can not conme here\n",buf,n,fp);
    }else
    {
        printf("fgets(%p,%d,%p) ok\n",buf,n,fp);
        print_char_buffer(result,n-1); // 字符串长 n-1 ，因为最后一个字符是 \0
    }
    return result;
}

int My_fputs(const char *str, FILE *fp)
{
    int result=fputs(str,fp);
    if(EOF==result)
        printf("fputs(\"%s\",%p) failec,because %s\n",str,fp,strerror(errno));
    else
        printf("fputs(\"%s\",%p) ok\n",str,fp);
    return result;
}

size_t My_fread(void *ptr, size_t size, size_t nobj, FILE *fp)
{
    size_t result=fread(ptr,size,nobj,fp);
    if(result<nobj)
    {

        if(feof(fp))
                    printf("fread(%p,%d,%d,%p) returns %d , because EOF\n"
                           ,ptr,size,nobj,fp,result);
        else if(ferror(fp))
            printf("fread(%p,%d,%d,%p) returns %d , because an error:%s\n"
                   ,ptr,size,nobj,fp,result,strerror(errno));
        else
            printf("fread(%p,%d,%d,%p) can not come here\n",ptr,size,nobj,fp);

    }else
    {
        printf("fread(%p,%d,%d,%p) ok\n",ptr,size,nobj,fp);
    }
    printf("fread read %d objects:",result);
    print_struct_buffer(ptr,result);
    return result;
}

size_t My_fwrite(const void *ptr, size_t size, size_t nobj, FILE *fp)
{
    size_t result=fwrite(ptr,size,nobj,fp);
    if(result<nobj)
    {
        printf("fwrite(%p,%d,%d,%p) returns %d,because an error :%s\n",
               ptr,size,nobj,fp,result,strerror(errno));
    }else
    {
        printf("fwrite(%p,%d,%d,%p) ok\n",ptr,size,nobj,fp);
    }
    return result;
}

off_t My_ftello(FILE *fp)
{
    off_t result=ftello(fp);
    if(-1==result)
    {
        printf("ftello(%p) failed,because %s\n",fp,strerror(errno));
    }else
        printf("ftello(%p) ok,offset is %d\n",fp,result);
    return result;
}
int My_fseeko(FILE *fp, off_t offset, int whence)
{
    int result=fseeko(fp,offset,whence);
    if(-1==result)
        printf("fseeko(%p,%d,%d) failed,because %s\n",
               fp,offset,whence,strerror(errno));
    else
        printf("fseeko(%p,%d,%d) ok\n",fp,offset,whence);
    return result;
}
void _test_read_write_char(FILE *fp)
{
    My_ftello(fp);   // 查看当前位置
    My_fgetc(fp);   // 读取一个字符
    //**** 写入 ****//
    My_fputc('a',fp); //写入一个字符
    My_ftello(fp); // 查看当前位置
    My_fputc('b',fp);
    My_ftello(fp); // 查看当前位置
    fflush(fp);
    //*** 读取 ****//
    My_fgetc(fp); // 读取一个字符
    My_fseeko(fp,0,SEEK_SET); //重定位到文件头
    My_ftello(fp); // 查看当前位置
    My_fgetc(fp); // 读取一个字符
    My_fgetc(fp); // 读取一个字符
    My_ungetc('c',fp);
    My_ferror(fp);
    My_feof(fp);
    My_fgetc(fp);
}

void _test_read_write_line(FILE *fp)
{
    char buffer[8];
    My_ftello(fp);   // 查看当前位置
    My_fgets(buffer,8,fp);
    //**** 写入 ****//
    My_fputs("abcdefg\nhijklmn\n",fp); // 每次7个字符加一个换行符
    My_ftello(fp);   // 查看当前位置
    My_fputs("0123456789",fp); // 没有换行符
    My_ftello(fp);   // 查看当前位置
    fflush(fp);
    //**** 读取 ****//
    My_fgets(buffer,8,fp);
    My_fseeko(fp,0,SEEK_SET); //重定位到文件头
    My_ftello(fp); // 查看当前位置
    My_fgets(buffer,8,fp); // 读取 abcdefg
    My_fgets(buffer,8,fp); // 读取 \n
    My_fgets(buffer,8,fp); // 读取 hijklmn
    My_fgets(buffer,8,fp); // 读取 \n
    My_fgets(buffer,8,fp); // 读取 0123456
    My_fgets(buffer,8,fp);// 读取 789
    My_fgets(buffer,8,fp);// 遇到 EOF
    My_fgets(buffer,8,fp);// 遇到 EOF
    My_fgets(buffer,8,fp);// 遇到 EOF

}
void _test_read_write_binary(FILE *fp)
{
    struct Struct_Data buffer[16];
    My_ftello(fp);   // 查看当前位置
    My_fread(buffer,sizeof(struct Struct_Data),16,fp);
    //**** 写入 ****//
    for(int i=0;i<16;i++)
    {
        buffer[i].int_i=i;
        buffer[i].int_j=i+1;
    }
    My_fwrite(buffer,sizeof(struct Struct_Data),8,fp);
    My_ftello(fp);   // 查看当前位置
    fflush(fp);
    //**** 读取 ****//
    My_fread(buffer,sizeof(struct Struct_Data),16,fp);
    My_fseeko(fp,0,SEEK_SET); //重定位到文件头
    My_ftello(fp); // 查看当前位置
    My_fread(buffer,sizeof(struct Struct_Data),16,fp);
}

void test_get_put_seek()
{
    M_TRACE("---------  Begin test_get_put_seek()  ---------\n");
    assert(prepare_file("test_char",NULL,0,S_IRWXU)==0);
    assert(prepare_file("test_line",NULL,0,S_IRWXU)==0);
    assert(prepare_file("test_binary",NULL,0,S_IRWXU)==0);

    FILE *file_char=My_fopen("test_char","r+");
    FILE *file_line=My_fopen("test_line","r+");
    FILE *file_binary=My_fopen("test_binary","rb+");

    if((file_char!=NULL) && (file_line!=NULL) && (file_binary!=NULL))
    {
        printf("***** test read write char*****\n");
        _test_read_write_char(file_char);
        printf("\n\n***** test read write str*****\n");
        _test_read_write_line(file_line);
        printf("\n\n***** test read write binary*****\n");
        _test_read_write_binary(file_binary);
    }

    //*** 关闭文件  ***//
    if(file_char!=NULL) fclose(file_char);
    if(file_line!=NULL) fclose(file_line);
    if(file_binary!=NULL) fclose(file_binary);

    un_prepare_file("test_char");
    un_prepare_file("test_line");
    un_prepare_file("test_binary");
    M_TRACE("---------  End test_get_put_seek()  ---------\n\n");
}
