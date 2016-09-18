/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第四章：文件和目录。
 *
 * 这里是 symlink 函数和 readlink 函数的用法。 symlinkat 函数用法类似 symlink 函数用法。
 * readlinkat 函数用法类似 readlink 函数用法。
 *
 */
#include"symlink_readlink.h"
#include"../header.h"
#include<unistd.h>
#include<fcntl.h>

extern void print_file_type(const char*pathname);

int My_symlink(const char *actualpath, const char *sympath)
{
    int result=symlink(actualpath,sympath);
    if(-1==result)
    {
        printf("symlink(\"%s\",\"%s\") failed,because %s\n",actualpath,sympath,strerror(errno));
    }else
    {
        printf("symlink(\"%s\",\"%s\") ok\n",actualpath,sympath);
    }
    return result;
}
ssize_t My_readlink(const char *pathname, char *buf, size_t bufsize)
{
    ssize_t result=readlink(pathname,buf,bufsize);
    if(-1==result)
    {
        printf("readlink(\"%s\",%p,%d) failed,because %s\n",pathname,buf,bufsize,strerror(errno));
    }else
    {
        printf("readlink(\"%s\",%p,%d) ok\n",pathname,buf,bufsize);
        printf("readlink result is :\t\"");
        for(int i=0;i<result;i++)
            printf("%c",buf[i]);
        printf("\"\n");
    }
    return result;
}
void print_link_file(const char *pathname)
{
    int fd=open(pathname,O_WRONLY); // 跟随符号链接
    if(-1==fd)
    {
        printf("print_link_file(\"%s\") <open> failed,because %s\n",pathname,strerror(errno));
        return;
    }
    char buffer[128];
    int len=read(fd,buffer,128);
    if(-1==len)
    {
        printf("print_link_file(\"%s\") <read> failed,because %s\n",pathname,strerror(errno));
        close(fd);
        return;
    }
    printf(" open and read file \"%s\" is:\t \"",pathname);
    for(int i=0;i<len;i++)
        printf("%c",buffer[i]);
    printf("\"\n");
    close(fd);
}
void test_symlink_readlink()
{
    M_TRACE("---------  Begin test_symlink_readlink()  ---------\n");
    assert(prepare_file("test","abcdefg0123456",14,S_IRWXU)==0); // 准备 test 文件
    print_file_type("test"); // 查看 test 文件类型

    My_symlink("test","test_symlink"); // 创建软连接 test_symlink 到 test
    print_file_type("test_symlink"); // 查看 test_symlink 文件类型
    print_link_file("test_symlink"); // 由于open 是链接跟随，所以这里打印 test 的内容

    char buffer[128];
    My_readlink("test_symlink",buffer,128);

    un_prepare_file("test"); // 删除 test 文件
    un_prepare_file("test_symlink"); // 删除 test_symlink 文件
    M_TRACE("---------  End test_symlink_readlink()  ---------\n\n");
}
