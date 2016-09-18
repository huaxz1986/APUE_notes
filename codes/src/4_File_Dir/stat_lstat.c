/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 stat 函数和 lstat 函数的用法。 fstat 函数和 fstatat 函数用法类似 stat 函数用法
 *
 */
#include"stat_lstat.h"
#include"../header.h"
#include<string.h>
#include<errno.h>
#include"../3_File_IO/open_creat.h"
extern void print_timespec(struct timespec *tm);

int My_stat(const char *pathname, Stat *buf)
{
    int result=stat(pathname,buf);
    if(-1==result)
        printf("stat(\"%s\",%p) failed,because %s\n",pathname,buf,strerror(errno));
    else
    {
        printf("stat(\"%s\",%p) ok:\n",pathname,buf);
        print_stat_type(buf,pathname);
        print_mode_perms(buf->st_mode,pathname);
        print_stat_owners(buf,pathname);
    }
}
int My_lstat(const char *pathname, Stat *buf)
{
    int result=lstat(pathname,buf);
    if(-1==result)
        printf("lstat(\"%s\",%p) failed,because %s\n",pathname,buf,strerror(errno));
    else
    {
        printf("lstat(\"%s\",%p) ok:\n",pathname,buf);
        print_stat_type(buf,pathname);
        print_mode_perms(buf->st_mode,pathname);
        print_stat_owners(buf,pathname);
    }
}
void print_stat_type(const Stat *file_stat, const char *file_name)
{
    printf(" \"%s\" type is:",file_name);
    if(S_ISREG(file_stat->st_mode))     printf("regular file,\t") ;
    if(S_ISDIR(file_stat->st_mode))     printf("directory file,\t") ;
    if(S_ISCHR(file_stat->st_mode))     printf("char file,\t") ;
    if(S_ISBLK(file_stat->st_mode))     printf(" block file,\t") ;
    if(S_ISFIFO(file_stat->st_mode))    printf("fifo  file,\t") ;
    if(S_ISLNK(file_stat->st_mode))     printf("link file,\t") ;
    if(S_ISSOCK(file_stat->st_mode))    printf("socket,\t") ;
    if(S_TYPEISMQ(file_stat))           printf("message queue file,\t") ;
    if(S_TYPEISSEM(file_stat))          printf("semaphore,\t") ;
    if(S_TYPEISSHM(file_stat))          printf("share memory,\t") ;
    printf("\n");
}

void print_mode_perms(mode_t mode, const char *file_name)
{
    printf("\"%s\" permission is:",file_name);
    if(S_IRUSR&mode)  printf("user read,\t");
    if(S_IWUSR&mode)  printf("user write,\t");
    if(S_IXUSR&mode)  printf("user exec,\t");
    if(S_IRGRP&mode)  printf("group read,\t");
    if(S_IWGRP&mode)  printf("group write,\t");
    if(S_IXGRP&mode)  printf("group exec,\t");
    if(S_IROTH&mode)  printf("other read,\t");
    if(S_IWOTH&mode)  printf("other write,\t");
    if(S_IXOTH&mode)  printf("other exec,\t");
    printf("\n");
}
void print_stat_owners(const Stat *file_stat, const char *file_name)
{
    printf("\"%s\" file ids:",file_name);
    printf("owner id < %d >,\t",file_stat->st_uid);
    printf("group id < %d >,\t",file_stat->st_gid);
    if(S_ISUID&file_stat->st_mode)  printf("set_user_id,\t");
    if(S_ISGID&file_stat->st_mode)  printf("set_group_id,\t");
    printf("\n");
}
void print_file_type(const char *pathname)
{
    Stat buf;
    if(-1!=stat(pathname,&buf))
        print_stat_type(&buf,pathname);
    else
        printf("get type of file \"\%s\" failed,because %s\n",pathname,strerror(errno));
}
int file_is_dir(const char *pathname)
{
    Stat buf;
    if(-1==stat(pathname,&buf))
    {
        printf("file_is_dir of file \"\%s\" failed,because %s\n",pathname,strerror(errno));
        return -1;
    }
    return S_ISDIR(buf.st_mode);
}

void print_file_perm(const char *pathname)
{
    Stat buf;
    if(-1!=stat(pathname,&buf))
        print_mode_perms(buf.st_mode,pathname);
    else
        printf("get perm of file \"\%s\" failed,because %s\n",pathname,strerror(errno));
}
void print_file_owner(const char *pathname)
{
    Stat buf;
    if(-1!=stat(pathname,&buf))
        print_stat_owners(&buf,pathname);
    else
        printf("get owners of file \"\%s\" failed,because %s\n",pathname,strerror(errno));
}
void print_file_size(const char *pathname)
{
    Stat buf;
    if(-1!=stat(pathname,&buf))
    {
        printf("file \"%s\" size is %d bytes\n",pathname,buf.st_size);
        printf("file \"%s\" block size is %d bytes\n",pathname,buf.st_blksize);
        printf("file \"%s\" blocks is %d \n",pathname,buf.st_blocks);
    }
    else
    {
        printf("get size of file  \"%s\" failed,because %s\n",pathname,strerror(errno));
    }
}
void print_file_link_num(const char *pathname)
{
    Stat buf;
    if(-1!=stat(pathname,&buf))
    {
        printf("hard link num of file \"%s\" is %d \n",pathname,buf.st_nlink);
    }
    else
    {
        printf("get hard link num  of file  \"%s\" failed,because %s\n",pathname,strerror(errno));
    }
}
void print_file_time(const char *pathname)
{
    Stat buf;
    if(-1!=stat(pathname,&buf))
    {
        printf("last data access time of file \"%s\" is :",pathname);
        print_timespec(&buf.st_atim);
        printf("last data modified time of file \"%s\" is :",pathname);
        print_timespec(&buf.st_mtim);
        printf("last i-node modified time of file \"%s\" is :",pathname);
        print_timespec(&buf.st_ctim);
    }
    else
    {
        printf("get time  of file  \"%s\" failed,because %s\n",pathname,strerror(errno));
    }
}

void test_stat_lstat()
{
    M_TRACE("---------  Begin test_stat_lstat()  ---------\n");
    assert(prepare_file("test",NULL,0,S_IRWXU)==0);


    Stat stat_buf;
    My_stat("test",&stat_buf); // regular file
    My_stat("/home/",&stat_buf); // dir file
    My_stat("/dev/loop0",&stat_buf); // block file
    My_stat("/dev/mem",&stat_buf); // char file
    My_lstat("/dev/cdrom",&stat_buf); // link file
    My_stat("/run/systemd/initctl/fifo",&stat_buf); // fifo file

    un_prepare_file("test");
    M_TRACE("---------  End test_stat_lstat()  ---------\n\n");
}
