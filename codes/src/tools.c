/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   tools 源文件
 *
 * 主要是定义了一些工具函数
 *
 */

#include"tools.h"
#include<sys/fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

extern char *strerror (int __errnum);
extern int unlink(const char*pathname);
extern int My_open_with_mode(const char*path,int oflag,mode_t mode);
extern ssize_t My_write(int fd,const void *buf,size_t nbytes);
int prepare_file(const char *pathname, const void *buffer, int len,mode_t mode)
{
    if(-1==unlink(pathname)) // 如果删除失败，且原因不是 ENOENT ，则返回 false
        if(errno!=ENOENT) return -1 ;
    int fd=open(pathname,O_CREAT|O_RDWR,mode); // 打开失败
    if(-1==fd)
    {
        printf("prepare file \"%s\" failed,because %s\n",pathname,strerror(errno));
        return -1;
    }
    if(len>0 && buffer!=NULL)
    {
        if(-1==write(fd,buffer,len))// 写文件失败
        {
            printf("prepare file \"%s\" failed,because %s\n",pathname,strerror(errno));
            close(fd);
            return -1;
        }
    }
    close(fd);
    return 0; // 创建成功
}

void un_prepare_file(const char *pathname)
{
    unlink(pathname);
}


void print_char_buffer(const char *buf, int n)
{
    printf("char buffer is:");
    for(int i=0;i<n;i++)
    {
        if(0==buf[i]) break;  // 终止符
        printf("%c",buf[i]);
    }
    printf("\n");
}

void fcntl_lock(int fd)
{
    struct flock data;
    data.l_type=F_WRLCK;
    data.l_whence=SEEK_SET;
    data.l_start=0;
    data.l_len=0; // 整个文件
    int result=fcntl(fd,F_SETLKW,&data); // F_SETLKW 为阻塞版本
    if(-1==result)
    {
        printf("fcntl_lock failed,because %s\n",strerror(errno));
    }
}
void fcntl_unlock(int fd)
{
    struct flock data;
    data.l_type=F_UNLCK;
    data.l_whence=SEEK_SET;
    data.l_start=0;
    data.l_len=0; // 整个文件
    int result=fcntl(fd,F_SETLKW,&data); // F_SETLKW 为阻塞版本
    if(-1==result)
    {
        printf("fcntl_unlock failed,because %s\n",strerror(errno));
    }
}

char* abs_path(const char *dir_name, const char *file_name)
{
    static char buffer[1024];
    if(NULL==dir_name )
    {
        printf("dir_name must not be NULL\n");
        return NULL;
    }
    if(NULL==file_name)
    {
        printf("file_name must not be NULL\n");
        return NULL;
    }
    if(dir_name[0]!='/')
    {
        printf("dir_name must start with '/'\n");
        return NULL;
    }
    if('/'==file_name[0])
    {
        printf("file_name must not start with '/'\n");
        return NULL;
    }
    strcpy(buffer,dir_name); // 拷贝
    strcat(buffer,"/"); //拼接
    strcat(buffer,file_name); //拼接
    return buffer;
}
