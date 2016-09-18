/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第六章：系统数据文件和信息。
 *
 * 这里是访问系统数据文件的相关函数的测试。
 *
 */
#include"system_file.h"
#include"../header.h"
#include <arpa/inet.h>

struct passwd* My_getpwuid(uid_t uid)
{
    struct passwd* result=getpwuid(uid);
    if(NULL==result)
        printf("getpwuid(%d) failed,because %s\n",uid,strerror(errno));
    else
    {
        printf("getpwuid(%d) ok:\t",uid);
        print_passwd(result);
    }
    return result;
}
struct passwd* My_getpwnam(const char *name)
{
    struct passwd* result=getpwnam(name);
    if(NULL==result)
        printf("getpwnam(\"%s\") failed,because %s\n",name,strerror(errno));
    else
    {
        printf("getpwnam(\"%s\") ok:\t",name);
        print_passwd(result);
    }
    return result;
}
struct passwd* My_getpwent()
{
    struct passwd* result=getpwent();
    if(NULL==result)
    {
        if(errno!=0) // 出现错误
            printf("getpwent() failed,because %s\n",strerror(errno));
        else  // EOF
            printf("getpwent() at the EOF\n");
    }else
    {
        printf("getpwent() ok\n");
        print_passwd(result);
    }
    return result;
}

struct spwd* My_getspnam(const char*name)
{
    struct spwd* result=getspnam(name);
    if(NULL==result)
        printf("getspnam(\"%s\") failed,because %s\n",name,strerror(errno));
    else
    {
        printf("getspnam(\"%s\") ok:\t",name);
        print_spwd(result);
    }
    return result;
}
struct spwd* My_getspent(void)
{
    struct spwd* result=getspent();
    if(NULL==result)
    {
        if(errno!=0) // 出现错误
            printf("getspent() failed,because %s\n",strerror(errno));
        else  // EOF
            printf("getspent() at the EOF\n");
    }else
    {
        printf("getspent() ok\n");
        print_spwd(result);
    }
    return result;
}


struct group* My_getgrgid(gid_t gid)
{
    struct group* result=getgrgid(gid);
    if(NULL==result)
        printf("getgrgid(%d) failed,because %s\n",gid,strerror(errno));
    else
    {
        printf("getgrgid(%d) ok:\t",gid);
        print_group(result);
    }
    return result;
}
struct group* My_getgrnam(const char* name)
{
    struct group* result=getgrnam(name);
    if(NULL==result)
        printf("getgrnam(\"%s\") failed,because %s\n",name,strerror(errno));
    else
    {
        printf("getgrnam(\"%s\") ok:\t",name);
        print_group(result);
    }
    return result;
}
struct group *My_getgrent(void)
{
    struct group* result=getgrent();
    if(NULL==result)
    {
        if(errno!=0) // 出现错误
            printf("getgrent() failed,because %s\n",strerror(errno));
        else  // EOF
            printf("getgrent() at the EOF\n");
    }else
    {
        printf("getgrent() ok\n");
        print_group(result);
    }
    return result;
}
/*!
 * \brief print_grouplist : 打印附属组列表
 * \param gidsetsize : 附属组的项目数
 * \param grouplist : 附属组的地址
 */
static void print_grouplist(int gidsetsize,gid_t grouplist[])
{
    printf("grouplist is:");
    for(int i=0;i<gidsetsize;i++)
        printf("\t%d,");
    printf("\n");
}
int My_getgroups(int gidsetsize,gid_t grouplist[])
{
    int result=getgroups(gidsetsize,grouplist);
    if(-1==result)
        printf("getgroups(%d,%p) failed,because %s\n"
               ,gidsetsize,grouplist,strerror(errno));
    else
    {
        printf("getgroups(%d,%p) ok,returns %d items\n" ,gidsetsize,grouplist,result);
        print_grouplist(result,grouplist);
    }
    return result;
}
int My_setgroups(int ngroups,const gid_t grouplist[])
{
    int result=setgroups(ngroups,grouplist);
    if(-1==result)
        printf("setgroups(%d,%p) failed,because %s\n"
               ,ngroups,grouplist,strerror(errno));
    else
        printf("setgroups(%d,%p) ok\n",ngroups,grouplist);
    return result;
}
int My_initgroups(const char *username, gid_t basegid)
{
    int result=initgroups(username,basegid);
    if(-1==result)
        printf("initgroups(\"%s\",%d) failed,because %s\n"
               ,username,basegid,strerror(errno));
    else
        printf("initgroups(\"%s\",%d) ok\n",username,basegid);
    return result;
}

int My_uname(struct utsname *name)
{
    int result=uname(name);
    if(-1==result)
    {
        printf("uname(%p) failed,because %s\n",name,strerror(errno));
    }else
    {
        printf("uname(%p) ok\n",name);
        print_utsname(name);
    }
    return result;
}
int My_gethostname(char *name, int namelen)
{
    int result=gethostname(name,namelen);
    if(-1==result)
        printf("gethostname(%p,%d) failed,because %s\n",
               name,namelen,strerror(errno));
    else
    {
        printf("gethostname(%p,%d) ok,host name is:\t",name,namelen);
        print_char_buffer(name,namelen);
    }
    return result;
}
struct hostent * My_gethostent(void)
{
    struct hostent * result=gethostent();
    if(NULL==result)
        printf("gethostent() failed,because %s\n",strerror(errno));
    else
    {
        printf("gethostent() ok:\t");
        print_hostent(result);
    }
    return result;
}

void print_passwd(const struct passwd *data)
{
    printf("struct passwd：");
    if(NULL==data)
    {
        printf("NULL\n");
        return;
    }
    printf("\n\tuser name：%s;",data->pw_name);
    printf("\n\tuser password：%s;",data->pw_passwd);
    printf("\n\tuser id：%d;",data->pw_uid);
    printf("\n\tuser gid：%d",data->pw_gid);
    printf("\n\tinitial work dir：%s;",data->pw_dir);
    printf("\n\tinitial shell：%s\n",data->pw_shell);
}
void print_spwd(const struct spwd *data)
{
    printf("struct spwd：");
    if(NULL==data)
    {
        printf("NULL\n");
        return;
    }
    printf("\n\tuser name：%s;",data->sp_namp);
    printf("\n\tuser encrypt password：%s;",data->sp_pwdp);
    printf("\n\tsince last changed：%d;",data->sp_lstchg);
    printf("\n\tnext changed after：%d;",data->sp_min);
    printf("\n\tnext change before：%d;",data->sp_max);
    printf("\n\twarn after：%d;",data->sp_warn);
    printf("\n\tinactive after：%d;",data->sp_inact);
    printf("\n\texpire after：%d;",data->sp_expire);
    printf("\n\tunuse：%d\n",data->sp_flag);
}
void print_group(const struct group *data)
{
    printf("struct group：");
    if(NULL==data)
    {
        printf("NULL\n");
        return;
    }
    printf("\n\tgroup name：%s;",data->gr_name);
    printf("\n\tgroup password：%s;",data->gr_passwd);
    printf("\n\tgroup id：%d;",data->gr_gid);
    printf("\n\tusers in group：<");
    char **item=data->gr_mem; //指向各用户名指针的数组
    //它是一个指针数组，其中每个指针指向一个属于该组的用户名。该数组以`null`指针结尾
    while(*item)
    {
        printf("%s\t",*item);
        item++;
    }
    printf(">\n");
}
void print_hostent(const struct hostent *data)
{
    printf("struct hostent：");
    if(NULL==data)
    {
        printf("NULL\n");
        return;
    }
    printf("\n\thost name：%s;",data->h_name);
    printf("\n\thost h_aliases：<");
    char **item=data->h_aliases;//它是一个指针数组，其中每个指针指向一个别名字符串。该数组以`null`指针结尾
    while(*item!=NULL)
    {
        printf("%s,\t",*item);
        item++;
    }
    printf(">;");
    printf("\n\thost address type：%d;",data->h_addrtype);
    printf("\n\thost address length：%d;",data->h_length);
    printf("\n\thost address_list：<");
    item=data->h_addr_list;//它是一个指针数组，其中每个指针指向一个地址名。该数组以`null`指针结尾
    //h_addr_list保存的并不是真正的字符串，而是指向struct in_addr类型的指针
    while(*item!=NULL)
    {
        struct in_addr * addr=(struct in_addr *)(*item);
        printf("%s,\t",inet_ntoa(*addr));
        item++;
    }
    printf(">\n");
}
void print_utsname(const struct utsname *data)
{
    printf("struct utsname");
    if(NULL==data)
    {
        printf("NULL\n");
        return;
    }
    printf("\n\tsysname:%s;",data->sysname);
    printf("\n\tnodename:%s;",data->nodename);
    printf("\n\trelease:%s;",data->release);
    printf("\n\tversion:%s;",data->version);
    printf("\n\tmachine:%s;",data->machine);
    printf("\n");
}
void _test_passwd()
{
    My_getpwuid(0);
    My_getpwuid(999); //不存在
    My_getpwnam("huaxz1986");
    My_getpwnam("huaxz1"); //不存在

    struct passwd * entry;
    while((entry=My_getpwent())!=NULL)
        ;
    endpwent();
}
void _test_shadow()
{
    My_getspnam("huaxz1986");
    My_getspnam("huaxz1"); //不存在

    struct spwd *entry;
    while((entry=My_getspent())!=NULL)
        ;
    endspent();
}
void _test_group()
{
    My_getgrgid(0);
    My_getgrgid(999); //不存在
    My_getgrnam("huaxz1986");
    My_getgrnam("huaxz1"); //不存在
    struct group * entry;
    while((entry=My_getgrent())!=NULL)
        ;
    endgrent();
}
void _test_attach_groups()
{
    gid_t grouplist[1024];
    My_getgroups(1024,grouplist);
    My_initgroups("huaxz1986",0);
}
void _test_host()
{
    struct utsname name;
    char buffer[1024];
    My_uname(&name);
    My_gethostname(buffer,1024);

    struct hostent * entry;
    while((entry=My_gethostent())!=NULL)
        ;
    endhostent();

}


void test_system_file()
{
    M_TRACE("---------  Begin test_system_file()  ---------\n");
    printf("********* test passwd ************\n");
    _test_passwd();
    printf("\n\n********* test shadow ************\n");
    _test_shadow();
    printf("\n\n********* test group ************\n");
    _test_group();
    printf("\n\n********* test attach groups ************\n");
    _test_attach_groups();
    printf("\n\n********* test host ************\n");
    _test_host();
    M_TRACE("---------  End test_system_file()  ---------\n\n");
}
