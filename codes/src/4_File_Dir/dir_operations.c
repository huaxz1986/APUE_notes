/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是目录相关的操作函数。 包括 mkdir 函数、 rmdir 函数、
 *  opendir 函数、 readdir 函数、 rewinddir  函数、closedir 函数、
 *  telldir 函数、 seekdir的用法。
 *
 * mkdirat 函数用法类似 mkdir 函数。 fchdir 函数用法类似 chdir 函数。
 * fdopendir 函数用法类似 opendir 函数。
 *
 */
#include"dir_operations.h"
#include"../header.h"
#include<unistd.h>

int file_is_dir(const char *pathname);


int My_mkdir(const char *pathname, mode_t mode)
{
    int result=mkdir(pathname,mode);
    if(-1==result)
    {
        printf("mkdir(\"%s\",%d) failed,because %s\n",pathname,mode,strerror(errno));
    }else
    {
        printf("mkdir(\"%s\",%d) ok\n",pathname,mode);
    }
    return result;
}
int My_rmdir(const char *pathname)
{
    int result=rmdir(pathname);
    if(-1==result)
    {
        printf("rmdir(\"%s\") failed,because %s\n",pathname,strerror(errno));
    }else
    {
        printf("rmdir(\"%s\") ok\n",pathname);
    }
    return result;
}

DIR* My_opendir(const char *pathname)
{
    DIR *result=opendir(pathname);
    if(NULL==result)
    {
        printf("opendir(\"%s\") failed,because %s\n",pathname,strerror(errno));
    }else
    {
        printf("opendir(\"%s\") ok\n",pathname);
    }
    return result;
}
struct dirent *My_readdir(DIR *dp)
{
    struct dirent * result=readdir(dp);
    if(NULL==result)
    {
        printf("readdir(%p) failed,because %s\n",dp,strerror(errno));
    }else
    {
        printf("readdir(%p) ok\n",dp);
    }
    return result;
}
long My_telldir(DIR *dp)
{
    long result=telldir(dp);
    if(-1==result)
    {
        printf("telldir(%p) failed,because %s\n",dp,strerror(errno));
    }else
    {
        printf("readdir(%p) ok\n",dp);
    }
    return result;
}
int My_chdir(const char *pathname)
{
    int result=chdir(pathname);
    if(-1==result)
    {
        printf("chdir(\"%s\") failed,because %s\n",pathname,strerror(errno));
    }else
    {
        printf("chdir(\"%s\") ok\n",pathname);
    }
    return result;
}
char *My_getcwd(char *buf,size_t size)
{
    char * result=getcwd(buf,size);
    if(NULL==result)
    {
         printf("chdir(%p,%d) failed,because %s\n",buf,size,strerror(errno));
    }else
    {
        printf("getcwd(%p,%d) ok\n",buf,size);
    }
    return result;
}
void print_cwd()
{
    char buf[1024];
    if(NULL==getcwd(buf,1024))
    {
        printf("print_cwd failed,because %s\n",strerror(errno));
    }else
    {
        printf("current work dir is :%s\n",buf);
    }
}
void print_dir(const char *pathname)
{
    //****** 子目录前缀：每个子层前缀多一个 '\t'
    static char prefix_buffer[1024];
    static char prefix_num=0;
    prefix_num++;
    prefix_buffer[prefix_num-1]='\t';

    //******* 深度优先遍历
    DIR * dir;
    struct dirent * dir_ent;
    dir=My_opendir(pathname);
    if(NULL==dir) return;
    printf("%s contents is :\n",pathname);
    while((dir_ent=My_readdir(dir)) !=NULL)
    {
        printf("\tid:<%d>, file_name :<%s>\n",dir_ent->d_ino,dir_ent->d_name);

        //*** 拼接路径
        char child_pathname[1024]="";
        strcat(child_pathname,pathname);
        strcat(child_pathname,"/");
        strcat(child_pathname,dir_ent->d_name);
        // 递归子目录
        if(1==file_is_dir(child_pathname))
            if(strcmp(dir_ent->d_name,".")!=0 && (0!=strcmp(dir_ent->d_name,"..")))
            {
                print_dir(child_pathname);
            }
    }
    printf("\n");
    closedir(dir);

    //****** 前缀回退
    prefix_buffer[prefix_num-1]=0;
    prefix_num--;
}

void test_dir_operations()
{
    M_TRACE("---------  Begin test_dir_operations()  ---------\n");
    //*** 创建目录 ****
    My_mkdir("test",S_IRWXU);
    My_mkdir("test/test1",S_IRWXU);

    //*** 创建文件
    prepare_file("test/tfile_1",NULL,0,S_IRWXU);
    prepare_file("test/tfile_2",NULL,0,S_IRWXU);
    prepare_file("test/tfile_3",NULL,0,S_IRWXU);
    prepare_file("test/test1/tfile_11",NULL,0,S_IRWXU);
    prepare_file("test/test1/tfile_22",NULL,0,S_IRWXU);
    prepare_file("test/test1/tfile_33",NULL,0,S_IRWXU);

    print_dir("test");

    print_cwd();
    My_chdir("test");
    print_cwd();
    My_chdir("../"); // 切换回来，否则后面的删除文件都会失败（因为都是相对路径）
    print_cwd();
    //***** 清理
    My_rmdir("test"); // 目录非空，删除失败！
    un_prepare_file("test/tfile_1");
    un_prepare_file("test/tfile_2");
    un_prepare_file("test/tfile_3");
    un_prepare_file("test/test1/tfile_11");
    un_prepare_file("test/test1/tfile_22");
    un_prepare_file("test/test1/tfile_33");
    My_rmdir("test/test1"); // 必须非空才能删除成功
    My_rmdir("test"); // 必须非空才能删除成功
    M_TRACE("---------  End test_dir_operations()  ---------\n\n");
}
