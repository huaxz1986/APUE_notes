# 文件和目录

## 一、 stat 结构和权限相关
1. 四个`stat`函数：返回文件或者目录的信息结构：

	```
	#include<sys/stat.h>
	int stat(const char * restrict pathname, struct stat*restrict buf);
	int fstat(int fd, struct stat* buf);
	int lstat(const char* restrict pathname,struct stat *restrict buf);
	int fstatat(int fd,const char*restrict pathname,struct stat*restrict buf,int flag);
	```

	- 参数：
		- `pathname`：文件或者目录的名字
		- `buf`：存放信息结构的缓冲区
		- `fd`：打开的文件描述符
			- 对于`fstat`，该文件就是待查看信息的文件
			- 对于`fstatat`，该文件是并不是待查看信息的文件。待查看信息的文件时已该`fd`对于的目录相对路径定位的
		- `flag`：控制着`fstatat`函数是否跟随一个符号链接。
	 	
		对于`fstatat`函数：

		- 待查看的文件名是由`fd`和`pathname`共同决定的。
			- 如果`pathname`是个绝对路径，则忽略`fd`参数
			- 如果`pathname`是个相对路径路径，且 `fd=AT_FDCWD`，则在当前工作目录的路径下查找`pathname`
			- 如果`pathname`是个相对路径路径，且 `fd!=AT_FDCWD`，则在`fd`对应的打开目录下查找`pathname`
		- `flag`：控制着`fstatat`函数是否跟随一个符号链接。当`!AT_SYMLINK_FOLLOW`标志被设置时，查看的是`pathname`（如果它是个符号链接）本身的信息；否则默认查看的是`pathname`（如果它是个符号链接）链接引用的文件的信息。	

	- 返回值：
		- 成功：返回 0
		- 失败： 返回 -1

	注意：
	- `lstat`类似于`stat`，但是当`pathname`是个符号链接时，`lstat`查看的是该符号链接的有关信息；而`stat`是查看该符号链接引用的文件的信息。
	- 在 `ubuntu 16.04`上，虽然有 `AT_SYMLINK_NOFOLLOW`这个常量，但是不支持。必须用 `!AT_SYMLINK_FOLLOW`。其常量定义为：
		- `AT_SYMLINK_FOLLOW`： 1024 (有效）
		- `!AT_SYMLINK_FOLLOW`： 0(有效）
		- `AT_SYMLINK_NOFOLLOW`： 256(无效）
		- `AT_SYMLINK_FOLLOW`： -1025(无效）
	

2. `stat`数据结构：其定义可能与具体操作系统相关，但是基本形式为：

	```
	struct stat{
	mode_t 			st_mode; 	//文件权限和类型信息
	ino_t 			st_ino;		//i-node 号
	dev_t 			st_dev;		// 设备号
	dev_t 			st_rdev;	// 特殊文件的设备号
	nlink_t 		st_nlink;	// 硬链接数量
	uid_t 			st_uid;		// owner 的用户ID
	gid_t 			st_gid;		// owner 的组ID
	off_t 			st_size;	//对普通文件，它是文件字节大小
	struct timespec st_atime;	// 上次访问时间
	struct timespec st_mtile;	// 上次修改时间
	struct timespec st_ctime;	// 上次文件状态改变的时间
	blksize_t 		st_blksize;	// 最佳的 I/O block 大小
	blkcnt_t 		st_blocks;	//分配的磁盘块数量
	}
	```

	其中`timespec`结构与具体操作系统相关，但是至少包括下面两个字段：

	```
	struct timespec{
	time_t tv_sec;	// 秒
	long tv_nsec; 	//纳秒
		}
```

3. UNIX 文件类型：
	- 普通文件：最常见的文件类型，这种文件包含了某种形式的数据。至于这种数据是二进制还是文本，对内核无区别。普通文件的内容解释由具体的应用程序进行。
	- 目录文件：这种文件包含了其他文件的名字，以及指向这些文件有关信息的指针。
		- 只有内核可以直接写目录文件（通常用户写目录文件都要通过内核）
		- 对某个目录文件具有读权限的任何一个进程都可以读取该目录的内容
	- 块特殊文件：这种类型的文件提供对设备（如磁盘）带缓冲的访问。每次访问以固定长度为单位进行。
	- 字符特殊文件：这种类型的文件提供对设备不带缓冲的访问，每次访问长度可变。
		> 系统的所有设备，要么是字符特殊文件，要么是块特殊文件
	- `FIFO`：这种类型的文件用于进程间通信，有时也称为命名管道
	- 套接字：这种类型的文件用于进程间的网络通信（也可用于单机上进程的非网络通信）
	- 符号链接：这种类型的文件指向另一个文件

	文件类型信息存放在`stat.st_mode`成员中，可以用下列的宏测试文件类型：
	- `S_ISREG()`：测试是否普通文件
	- `S_ISDIR()`：测试是否目录文件
	- `S_ISCHR()`：测试是否字符特殊文件
	- `S_ISBLK()`：测试是否块特殊文件
	- `S_ISFIFO()`：测试是否`FIFO`
	- `S_ISLNK()`：测试是否符号链接文件
	- `S_ISSOCK()`：测试是否套接字

	另外 `POSIX.1` 允许将进程间通信对象说明为文件。但是下面的宏测试的不是`stat.st_mode`，而是`stat*`（`stat`指针）：
	- `S_TYPEISMQ()`：测试是否消息队列
	- `S_TYPEISSEM()`：测试是否信号量
	- `S_TYPEISSHM()`：测试是否共享存储对象

4. 与一个进程有关的ID有很多:
	- 实际用户 ID 和实际组 ID： 标志我们究竟是谁。当我们登录进操作系统时，这两个值就确定了！
	- 有效用户 ID、有效组ID、附属组 ID： 用于文件访问权限检查。
	- 保存的设置用户ID、保存的设置组ID：由 `exec`函数保存

	每个文件都有一个所有者和组所有者，分别有 `stat.st_uid`和`stat.st_gid`指定。当一个文件时可执行文件时，如果执行这个文件，那么进程的有效用户ID就是实际用户ID，有效组ID就是实际组ID，除了下面的情况：
	-  当在`stat.st_mode`中设置了一个特殊标志：设置用户ID位时，则将进程的有效用户ID设置为文件所有者的用户ID
	-  当在`stat.st_mode`中设置了一个特殊标志：设置组ID位时，则将进程的有效组ID设置为文件所有者的组ID
	> 任何进程都是由可执行文件被执行而得到。因此位于磁盘上的可执行文件的所属的用户ID和组ID会影响到进程的用户ID和组ID

	如果某个可执行文件所有者是`root`，且该文件的设置用户ID位已经被设置，那么无论谁执行这个可执行文件时，该可执行文件产生的进程就具有超级用户权限。

	设置用户ID位、设置组ID位 都包含在`stat.st_mode`中，可以通过下列两个宏测试：
	- `S_ISUID()`：测试是否设置了设置用户ID位
	- ·S_ISGID()`：测试是否设置了设置组ID位

5. 文件访问权限：所有文件类型（包括目录，字符特别文件等）都有访问权限。每个文件都有9个访问权限位：
	- `S_IRUSR`：用户读
	- `S_IWUSR`：用户写
	- `S_IXUSR`：用户执行
	- `S_IRGRP`：组读
	- `S_IWGRP`：组写
	- `S_IXGRP`：组执行
	- `S_IROTH`：其他读
	- `S_IWOTH`：其他写
	- `S_IXOTH`：其他执行

	访问权限规则：

	- 当用名字`pathname`打开任何一个类型的文件时，对`pathname`中包含的每一个目录，包括`pathname`可能隐含的当前工作目录都应该具有执行权限
		> 因此目录的执行权限位也称之为搜索位
	- 对一个文件的读权限决定了我们能否打开现有文件进行读操作
	- 对一个文件的写权限决定了我们能否打开现有文件进行写操作
	- 如果你在`open`函数中对一个文件指定了`O_TRUNC`标志，则必须对该文件具有写权限
	- 为了在一个目录中常见一个新文件，必须对该目录具有写权限和执行权限
	- 为了删除一个现有文件，必须对包含该文件的目录具有写权限和执行权限。对该文件本身没有权限的限制
	- 如果用7个`exec`函数中的任何一个执行某个文件，则必须对该文件具有执行权限，且该文件必须是个普通文件

	进程每次打开、创建、删除一个文件时，内核就进行文件访问权限测试。这种测试如下：

	- 若进程的有效用户ID是0（超级用户），则对该文件的任何访问行为都批准
	- 若进程的有效用户ID等于文件的所有者ID（也就是进程拥有此文件）：
		- 如果该文件的用户读权限开放，则内核允许进程读该文件
		- 如果该文件的用户写权限开放，则内核允许进程写该文件
		- 如果该文件的用户执行权限开放，则内核允许进程执行该文件
	- 若进程的有效组ID或者进程的附属组ID之一等于文件的组ID：
		- 如果该文件的组读权限开放，则内核允许进程读该文件
		- 如果该文件的组写权限开放，则内核允许进程写该文件
		- 如果该文件的用户执行权限开放，则内核允许进程执行该文件
	- 否则：
		- 如果该文件的其他读权限开放，则内核允许进程读该文件
		- 如果该文件的其他写权限开放，则内核允许进程写该文件
		- 如果该文件的其他户执行权限开放，则内核允许进程执行该文件

	只要有一个权限通过，则不再进行测试。若所有权限都不通过，则不允许访问。

6. 对一个目录的读权限和可执行权限是不同的：
	- 目录读权限：允许读目录，从而获得在该目录中所有文件名的列表
	- 目录可执行权限：允许搜索该目录，从而寻找一个特定的文件名

7. 当一个进程通过`open`或者`creat`创建一个新文件时：
	- 新文件的用户ID被设置为进程的有效用户ID
	- 新文件的组ID可以有两个值之一：
		- 进程的有效组ID
		- 文件所在目录的组ID
		> 具体选择哪个，由具体操作系统决定

8. 示例

	```
	#include <stdio.h>
	#include<sys/stat.h>
	#include<unistd.h>
	#include<fcntl.h>

	typedef struct stat Stat;

	void test_file_type(Stat* file_stat,const char* file_name)
	{
    	printf("\t%s type is:",file_name);
    	if(S_ISREG(file_stat->st_mode))
        	printf(" regular file,  ") ;
    	if(S_ISDIR(file_stat->st_mode))
        	printf("directory file  ") ;
    	if(S_ISCHR(file_stat->st_mode))
        	printf("char file,  ") ;
    	if(S_ISBLK(file_stat->st_mode))
       		 printf(" block file,  ") ;
   	if(S_ISFIFO(file_stat->st_mode))
       		 printf("fifo  file,  ") ;
    	if(S_ISLNK(file_stat->st_mode))
       		 printf("ink file,  ") ;
    	if(S_ISSOCK(file_stat->st_mode))
        	printf("socket,  ") ;
    	if(S_TYPEISMQ(file_stat))
        	printf("message queue file, ") ;
    	if(S_TYPEISSEM(file_stat))
       		 printf("semaphore,  ") ;
    	if(S_TYPEISSHM(file_stat))
       		 printf("share memory,  ") ;
    	printf("\n");
	}
	void test_file_id(Stat* file_stat,const char* file_name)
	{
   	 printf("\t%s file id:");
   	 printf("owner id < %d >, ",file_stat->st_uid);
    	printf("group id < %d >, ",file_stat->st_gid);
    	if(S_ISUID&file_stat->st_mode)
        	printf("set_user_id, ");
    	if(S_ISGID&file_stat->st_mode)
        	printf("set_group_id , ");
    	printf("\n");
	}
	void test_file_permission(Stat* file_stat,const char* file_name)
	{
   	 printf("\t%s file permission:");
    	if(S_IRUSR&file_stat->st_mode)
       	 	printf("user read, ");
    	if(S_IWUSR&file_stat->st_mode)
       		 printf("user write, ");
    	if(S_IXUSR&file_stat->st_mode)
       		 printf("user exec, ");
    	if(S_IRGRP&file_stat->st_mode)
        		printf("group read, ");
   	 if(S_IWGRP&file_stat->st_mode)
       		 printf("group write, ");
    	if(S_IXGRP&file_stat->st_mode)
       		 printf("group exec, ");
    	if(S_IROTH&file_stat->st_mode)
        	printf("other read, ");
    	if(S_IWOTH&file_stat->st_mode)
       		 printf("other write, ");
    	if(S_IXOTH&file_stat->st_mode)
        	printf("other exec, ");
    	printf("\n");
	}

	int main(int argc, char *argv[])
	{
    	Stat stat_buf;
   	int fd;
    	printf("Test regular file:\n");
    	stat("/home/huaxz1986/main.c",&stat_buf);
   	 test_file_type(&stat_buf,"/home/huaxz1986/main.c");
    	test_file_id(&stat_buf,"/home/huaxz1986/main.c");
    	test_file_permission(&stat_buf,"/home/huaxz1986/main.c");

    	printf("Test directory file:\n");
    	stat("/home/huaxz1986/file_dir",&stat_buf);
    	test_file_type(&stat_buf,"/home/huaxz1986/file_dir");
    	test_file_id(&stat_buf,"/home/huaxz1986/file_dir");
    	test_file_permission(&stat_buf,"/home/huaxz1986/file_dir");

   	 printf("Test block file:\n");
   	 stat("/dev/loop0",&stat_buf);
    	test_file_type(&stat_buf,"/dev/loop0E");
    	test_file_id(&stat_buf,"/dev/loop0");
    	test_file_permission(&stat_buf,"/dev/loop0");

    	printf("Test char file:\n");
    	stat("/dev/mem",&stat_buf);
    	test_file_type(&stat_buf,"/dev/mem");
    	test_file_id(&stat_buf,"/dev/mem");
    	test_file_permission(&stat_buf,"/dev/mem");

    	printf("Test link file:\n");
    	stat("/dev/cdrom",&stat_buf);
    	test_file_type(&stat_buf,"/dev/cdrom");
    	test_file_id(&stat_buf,"/dev/cdrom");
    	test_file_permission(&stat_buf,"/dev/cdrom");

    	printf("Test fifo file:\n");
   	 stat("/run/systemd/initctl/fifo",&stat_buf);
   	 test_file_type(&stat_buf,"/run/systemd/initctl/fifo");
   	 test_file_id(&stat_buf,"/run/systemd/initctl/fifo");
    	test_file_permission(&stat_buf,"/run/systemd/initctl/fifo");

    	printf("Create new file:\n");
   	 fd=openat(AT_FDCWD,"test",O_WRONLY|O_CREAT,S_IRUSR);
    	fstat(fd,&stat_buf);
    	test_file_type(&stat_buf,"./test");
    	test_file_id(&stat_buf,"./test");
    	test_file_permission(&stat_buf,"./test");

    	return 0;
	}
	```

  	![stat](../imgs/file_dir/stat.JPG) 

## 二、访问测试和文件模式创建屏蔽字

1. 当用`open()`函数打开一个文件时，内核根据进程的有效用户ID和有效组ID为依据来执行访问权限测试。但是如果你想测试进程的实际用户ID和实际组ID是否能够通过权限测试时，可以用下列两个函数：

	```
	#include<unistd.h>
	int access(const char *pathname,int mode);
	int faccess(int fd,const char*pathname,int mode,int flag);
	```
	- 参数：
		- `pathname`：文件路径名
		- `mode`：指定要测试的模式。
			- 如果要测试文件是否已存在，则`mode`设为`F_OK`
			- 如果要测试进程的实际用户ID和实际组ID的权限，则可以为下列常量的按位或
				- `R_OK`：测试读权限
				- `W_OK`：测试写权限
				- `X_OK`：测试执行权限

		对于 `faccess`函数：
		- `fd`：一个打开目录文件的描述符，或者`AT_FDCWD`
		- `pathname`：
			- 如果为绝对路径，则忽略`fd`参数
			- 如果为相对路径，则相对路径的目录由`fd`指定。
				- 若`fd=AT_FDCWD`，则表示相对于当前工作目录
				- 否则相对于`fd`对于的打开的目录
		- `flag`：如果是`AT_EACCESS`，则访问检查使用进程的有效用户ID和有效组ID，而不是实际用户ID和实际组ID

	- 返回值：
		- 成功：返回0
		- 出错： 返回 -1

2. 文件模式创建屏蔽字：当进程创建一个新的目录或者文件时，会使用文件模式创建屏蔽字。在文件模式创建屏蔽字中为1的位，在文件`mode`中的相应位一定被关闭。设置进程的文件模式创建屏蔽字的函数为：

	```
	#include<sys/stat.h>
	mode_t umask(mode_t cmask);
	```

	- 参数： 
		- `cmask`：要设置的新的文件模式创建屏蔽字
	- 返回值：
		- 成功：旧的文件模式创建屏蔽字
		- 函数未指定失败时返回何值

	如果你在通过`creat`或者`open`函数指定了`mode`，那么该`mode`必须通过文件模式创建屏蔽字的屏蔽之后才是最终新创建的文件的权限模式。
	> shell 有一个`umask`命令。我们可以通过该命令来设置或者打印当前的文件模式创建屏蔽字

3. 示例

	```
	#include<stdio.h>
	#include<unistd.h>
	#include<string.h>
	#include<errno.h>
	#include<sys/stat.h>
	#include<fcntl.h>
	typedef struct stat Stat;

	void test_access(const char*pathname,int mode)
	{
   	 int ok;
   	 printf("\tAccess %s:",pathname);
   	 ok=access(pathname,mode);
   	 if(ok==-1)
   	 {
      	  printf("failed! Beause %s \n",strerror(errno));
   	 }
    	else
    	{
        	printf("ok!\n");
   		 }
	}
	void test_umask(mode_t cmask)
	{
   		 mode_t old_mode;
   		 old_mode=umask(cmask);
   		 printf("\t old mask is:");
   		 print_mode(old_mode);
   		 printf("\t current mask is:");
   		 print_mode(cmask);
	}
	void print_mode(mode_t expected_mode)
	{
   	 if(S_IRUSR&expected_mode)
       		 printf("U_RD, ");
    	if(S_IWUSR&expected_mode)
       		 printf("U_WR, ");
  	  if(S_IXUSR&expected_mode)
      		  printf("U_EXC, ");
    	if(S_IRGRP&expected_mode)
      		  printf("G_RD, ");
   	if(S_IWGRP&expected_mode)
     		   printf("G_WR, ");
   	 if(S_IXGRP&expected_mode)
      		  printf("G_EXC, ");
   	 if(S_IROTH&expected_mode)
       		 printf("O_RD, ");
    	if(S_IWOTH&expected_mode)
      		  printf("O_WR, ");
  	  if(S_IXOTH&expected_mode)
       		 printf("O_EXC, ");
    	printf("\n");
	}

	void test_file_mode(int expected_mode,const char* file_name)
	{
  	 	 printf("\t Expected file mode:");
   		 print_mode(expected_mode);
   	 	Stat stat_buf;
   	 	int fd;
    		fd=openat(AT_FDCWD,file_name,O_CREAT|O_EXCL|O_RDWR,expected_mode);
    		if(fd==-1)
   		 {
       		 printf("open %s in test_file_mode,because %s",file_name,strerror(errno));
       		 return ;
    		}
   		 fstat(fd,&stat_buf);
   		 printf("\n \t Real file mode:");
   		 print_mode(stat_buf.st_mode);
   		 unlinkat(AT_FDCWD,"test_file",!AT_SYMLINK_FOLLOW);
	}

	int main(int argc, char *argv[])
	{
   	 printf("Test access: no exist file:\n");
   	 test_access("/no/exist",F_OK);
   	 printf("Test access: no write:\n");
   	 test_access("/etc/shadow",W_OK);
	printf("Test access: write ok:\n");
   	test_access("/home/huaxz1986/file_dir",W_OK);
   	 printf("\n\n\n");
   	 printf("Current creat file:\n");
   	 test_file_mode(S_IRWXU|S_IRWXG|S_IRWXO,"test1");
   	 printf("umask:\n");
   	 test_umask(S_IRUSR|S_IRGRP|S_IROTH);
   	 printf("After umask :\n");
   	 test_file_mode(S_IRWXU|S_IRWXG|S_IRWXO,"test2");
   	return 0;
	}
	```
  	![access_umask](../imgs/file_dir/access_umask.JPG) 

	可以看到：
	- `access`函数：对于不存在的文件名访问失败；对没有写权限的名字写访问失败
	-  被创建的文件的访问权限是由文件创建屏蔽字、创建文件时指定的权限二者共同作用的
	


## 三、修改文件访问权限和文件所属用户

1. 修改文件的现有的访问权限：

	```
	#include<sys/stat.h>
	int chmod(const char*pathname,mode_t mode);
	int fchmod(int fd,mode_t mode);
	int fchmodat(int fd,const char*pathname,mode_t mode,int flag);
	```

	- 参数：
		- `pathname`：文件路径名
		- `mode`：文件修改后的权限。

		对于 `fchmod`函数：
		- `fd`：打开的文件描述符

		对于 `fchmod`函数：
		- `fd`：一个打开目录文件的描述符，或者`AT_FDCWD`
		- `pathname`：
			- 如果为绝对路径，则忽略`fd`参数
			- 如果为相对路径，则相对路径的目录由`fd`指定。
				- 若`fd=AT_FDCWD`，则表示相对于当前工作目录
				- 否则相对于`fd`对于的打开的目录
		- `flag`：如果是`!AT_SYMLINK_FOLLOW`，则`fchmodtat`并不跟随符号链接

	- 返回值：
		- 成功：返回0
		- 出错： 返回 -1

	参数`mode`可以是下面常量的按位或：（来自头文件`<sys/stat.h>`
	- `S_ISUID`：执行时设置用户ID
	- `S_ISGID`：执行时设置组ID
	- `S_ISVTX`：粘着位
	- `S_IRWXU`：用户读、写和执行
	- `S_IRUSR`：用户读
	- `S_IWUSR`：用户写
	- `S_IXUSR`：用户执行
	- `S_IRWXG`：组读、写和执行
	- `S_IRGRP`：用户读
	- `S_IWGRP`：用户写
	- `S_IXGRP`：用户执行
	- `S_IRWXO`：其他读、写和执行
	- `S_IROTH`：用户读
	- `S_IWOTH`：用户写
	- `S_IXOTH`：用户执行

2. 粘着位：如果对一个目录设置了粘着位，则任何对该目录具有写权限的进程都能够在该目录中创建文件。但是：只有满足下列条件之一的用户才能删除或者重命名该目录下的文件：
	- 拥有此文件
	- 拥有此目录
	- 是超级用户
	> 对于未设置粘着位的目录，则只要用户对该目录有写权限，那么就有修改和重命名该目录下其他文件的能力

3. 修改用户的ID和组ID：

	```
	#include<unistd.h>
	int chown(const char *pathname,uid_t owner,gid_t group);
	int fchown(int fd,uid_t owner,gid_t group);
	int fchownat(int fd,const char *pathname,uid_t owner,gid_t group,int flag);
	int lchown(const char *pathname,uid_t owner,gid_t group);
	```
	- 参数：
		- `pathname`：文件路径名
		- `owner`：文件修改后的用户ID
		- `group`：文件修改后的组ID

		对于`fchown`函数：
		- `fd`：打开的文件描述符，要修改的就是这个文件

		对于 `fchmod`函数：

		- `fd`：一个打开目录文件的描述符，或者`AT_FDCWD`
		- `pathname`：
			- 如果为绝对路径，则忽略`fd`参数
			- 如果为相对路径，则相对路径的目录由`fd`指定。
				- 若`fd=AT_FDCWD`，则表示相对于当前工作目录
				- 否则相对于`fd`对于的打开的目录
		- `flag`：如果是`!AT_SYMLINK_FOLLOW`，则`fchmodtat`并不跟随符号链接，修改的是符号链接本身而不是符号链接指向的文件

	- 返回值：
		- 成功： 返回 0
		- 出错： 返回 -1

	有两点注意：
	- `lchown`函数更改的是符号链接本身，而`chown`遇到符号链接时更改的是符号链接指向的文件
	- 如果这些函数由非超级用户进程调用，则成功返回时，该文件的设置用户ID和设置组ID位都被清除

4. 示例

	```
	#include <stdio.h>
	#include<fcntl.h>
	#include<sys/stat.h>
	#include<unistd.h>
	#include<errno.h>
	#include<string.h>
	typedef struct stat Stat;
	void print_mode(mode_t expected_mode)
	{
  	  printf("\t");
    	if(S_IRUSR&expected_mode)
        	printf("U_RD, ");
    	if(S_IWUSR&expected_mode)
        	printf("U_WR, ");
   	 if(S_IXUSR&expected_mode)
        	printf("U_EXC, ");
    	if(S_IRGRP&expected_mode)
        	printf("G_RD, ");
    	if(S_IWGRP&expected_mode)
        	printf("G_WR, ");
   	if(S_IXGRP&expected_mode)
        	printf("G_EXC, ");
    	if(S_IROTH&expected_mode)
        	printf("O_RD, ");
    	if(S_IWOTH&expected_mode)
        	printf("O_WR, ");
    	if(S_IXOTH&expected_mode)
        	printf("O_EXC, ");
    	printf("\n");
	}


	int main(int argc, char *argv[])
	{
    	Stat stat_buf;
    	int fd;

    	fd=openat(AT_FDCWD,"test",O_CREAT|O_RDWR,S_IRWXU|S_IRWXG|S_IRWXO);
    	fstat(fd,&stat_buf);
   	 printf("Current mode:\n");
    	print_mode(stat_buf.st_mode);
    	printf("Current user: %d, current group: %d\n",stat_buf.st_uid,stat_buf.st_gid);

    	if(fchmod(fd,S_IRWXU)==-1)
    	{
       		 printf("chmod failed,beause of %s",strerror(errno));

   	 }else
    	{
        	printf("After Change mode:\n");
        	fstat(fd,&stat_buf);
        	print_mode(stat_buf.st_mode);

    	}

    	if(fchown(fd,1001,1001)==-1)
    	{
        	printf("chown failed,beause of %s\n",strerror(errno));

    	}else
    	{
       	fstat(fd,&stat_buf);
       	printf("After Change owner--> user : %d, current group: %
	d\n",stat_buf.st_uid,stat_buf.st_gid);
    	}

    	return 0;
	}

	```

  	![chmod_chown](../imgs/file_dir/chmod_chown.JPG) 

	可以看到：
	- 修改文件所属的用户和组，需要超级用户权限。普通用户无法修改，即使该用户就是该文件的所有者也不行

## 四、修改文件长度

1. 文件长度：`stat.st_size`字段存放的是以字节为单位的文件的长度。此字段只对普通文件、目录文件、符号链接才有意义：
	- 对普通文件：其长度就是文件的大小。长度为0表示该文件为空
	- 对目录文件：其长度通常是个整数（如16或者512）的整数倍
	- 对符号链接：其长度是符号链接本身存放的某个文件名的实际字节数（它并不包含字符串的`null`字节，因为这些字符是存放在文件中，而不是存放在内存中的字符串）

	另外`stat.st_blksize`存放的是对于文件 I/O 较合适的块长度；`stat.st_blocks`存放的是所分配的块的数量（一个块512字节）。注意：
	- 对于普通文件，可能包含空洞。空洞是由于设置的文件偏移量超过了文件末尾，然后写入了某些数据造成的。对于空洞文件：
		- 空洞文件的存储需要的磁盘块数量可能远小于文件大小。文件大小是文件末尾到文件头的字节数
		- 读取空洞文件的空洞时，对于没有写过的字节位置`read`返回的是字节0

2. 截断文件：通常可以用带`O_TRUNC`选项的`open()`函数来清空一个文件（截断到0）。但是如果希望截断文件使得文件大小为指定字节数，则可以用下列的函数：

	```
	#include<unistd.h>
	int truncate(const char*pathname,off_t length);
	int ftruncate(int fd,off_t length);
	```
	- 参数：
		- `pathname`：文件路径名
		- `length`：文件修改后大小（字节数）
		- `fd`：打开的文件描述符，要修改的就是这个文件
	- 返回值：
		- 成功： 返回 0
		- 出错： 返回 -1

	有两点注意：
	- 若`length`小于文件的原大小，则修改文件大小之后，文件新的尾端之后的位置不再可以访问
	- 若`length`大于文件的原大小，则修改文件大小之后，会形成空洞。即从文件原大小新的尾端形成了空洞

3. 示例

	```
	#include <stdio.h>
	#include<sys/stat.h>
	#include<string.h>
	#include<errno.h>
	#include<unistd.h>
	#include<fcntl.h>
	typedef struct stat Stat;
	void print_file_size(int fd)
	{
    	int ok;
    	Stat stat;
    	ok=fstat(fd,&stat);
    	if(ok==01)
    	{
       		 printf("\tfstat error,because of %s\n",strerror(errno));
    	}else
    	{
        	printf("\tfile size is :%d; blksize:%d; blocks:%d
		\n",stat.st_size,stat.st_blksize,stat.st_blocks);
    	}
	}
	void test_truncate(int fd,off_t len)
	{
    		int ok;
   		 ok=ftruncate(fd,len);
   		 if(ok==-1)
    		{
        		printf("\tftruncate error,because of %s\n",strerror(errno));
    		}else
    		{
        		print_file_size(fd);
    		}
	}
	void test_open_trunc(const char* filename)
	{
   	 	int fd;
    		fd=openat(AT_FDCWD,filename,O_TRUNC|O_RDWR);
    		if(fd==-1)
    		{
       		 printf("\topenat %s failed,because of %s\n",strerror(errno));
    		}else
    		{
        		print_file_size(fd);
    		}
	}
	void read_fd(int fd,int len)
	{
   	 	char bytes[2048];
    		int ok;
    		ok=read(fd,bytes,len);
    		int i;
    		if(ok==-1)
    		{
         		printf("\tread error,because of %s\n",strerror(errno));
    		}else
    		{
        		lseek(fd,0,SEEK_SET);
        		printf("\tthe bytes is:");
        		for(i=0;i<ok;i++)
        		{
            		printf("\t%d",bytes[i]);
        		}
        		printf("\n");
    		}
	}

	int main(int argc, char *argv[])
	{
    		int fd;

    		fd=openat(AT_FDCWD,"test",O_CREAT|O_RDWR,S_IRWXU);
   		 if(fd==-1)
       			 return;
    		write(fd,"abcdefg",8);
    		lseek(fd,0,SEEK_SET);
    		printf("Original size:\n");
    		print_file_size(fd);
    		printf("Truncate to 100\n");
    		test_truncate(fd,100);
    		read_fd(fd,100);
    		printf("Truncate to 2\n");
    		test_truncate(fd,2);
    		read_fd(fd,2);
    		close(fd);
   		 printf("Test open with trunc:\n");
   		 test_open_trunc("test");
   		read_fd(fd,0);
    		return 0;
	}

	```

  	![truncate](../imgs/file_dir/truncate.JPG) 

	可以看到：
	- 对于文件空洞，它不占用任何磁盘空间；空洞部分读出的内容全为0
	- 对于非常小的文件，比如这里的 8 字节文字，磁盘分配了 8个块（4kb）。

## 五、UNIX文件系统、硬链接、软链接、删除、重命名

1. UNIX文件系统简介(传统的基于BSD的UNIX文件系统，称作`UFS`）：
	- 一个磁盘可以划分成一个或者多个分区，每个分区可以包含一个文件系统。每个文件系统包含一些柱面组。每个柱面组包括：
		- 一个 i 节点图：用于指示哪些 i 节点已经被使用，哪些未被使用
		- 一个 块位图：用于指示哪些数据块已经被使用，哪些为被使用
		- 一个 i 节点组。它包含的是许多 i  节点。
		- 一个数据区：存放具体的数据块和目录块
	- 数据区包含两种类型的块：
		- 目录块：它的内容是 `<i 节点编号>|<文件名>` 这种格式的记录的列表
		- 数据块：它的内容就是具体文件的数据		
	- i 节点是固定长度的记录项，它包含有关文件的大部分信息
		- 每个 i 节点都有一个链接计数，其值是指向 i 节点的目录的项数(这种链接类型称之为硬链接)。只有当该链接计数减少为0时，才可以删除该链接文件（也就是释放该文件占用的数据块）。
			- 在`stat`结构中，链接计数包含在`st_nlink`成员中（POSIX常量：`LINK_MAX`指定了一个文件链接数的最大值）			 
		- 每个 i 节点包含了文件有关的所有信息：文件类型、文件权限访问位、文件长度和指向文件数据块的指针
			- `stat`结构中的大多数信息来自于 i  结点。只有两项重要数据存放在目录项中：文件名、i节点编号
		- 目录项中的 i 节点编号只能指向同一个文件系统中的相应的 i 节点。
			> 因此硬链接不能跨文件系统
		- 当在不更换文件系统的情况下重命名一个文件时，该文件的实际内容并未移动。只需要构造一个指向现有 i 节点的新目录项，并删除来的目录项。此时该 i节点的链接计数不会改变
			> 这就是 `mv`命令的操作方式

2. 与硬链接对应的概念是软链接。软链接也称作符号链接，它是一种特殊的文件。该文件的实际内容（在数据块中）包含了该符号链接所指向的文件的名字。同时该文件的 i 节点指示了该文件类型是 `S_IFLNK`，于是系统知道了这个文件是个符号链接。
	- 硬链接直接指向文件的`i`节点
	- 软链接是对一个文件的间接指针

	引入符号链接的原因是为了避开硬链接的一些限制：
	- 硬链接通常要求链接和文件位于同一个文件系统中
	- 只有超级用户才能创建指向目录的硬链接（在底层文件系统支持的情况下）

	对于符号链接以及它指向何种类型的文件并没有什么限制。任何用户都可以创建指向目录的符号链接。但是使用符号链接有可能在文件系统中引入循环

	对于处理文件和目录的函数，如果传递的是一个符号链接的文件名，则应该注意：函数是否跟随符号链接，即函数是处理符号链接指向的文件，还是处理符号链接本身。

	- 跟随符号链接（即处理符号链接指向的文件）的函数有：`access`、`chdir`、`chmod`、`chown`、`creat`、`exec`、`link`、`open`、`opendir`、`pathconf`、`stat`、`truncate`
	- 不跟随符号链接（即处理符号链接文件本身）的函数有：`lchown`、`lstat`、`readlink`、`remove`、`rename`、`unlink`
		- 一个例外的情况：如果用`O_CREAT`和`O_EXCL`选项调用`open`，此时若参数是个符号链接的文件名，则`open`出错返回（并不考虑符号链接指向的文件是否存在），同时将`errno`设为`EEXIST`

3. 任何一个目录 `dirxxx` 的硬链接至少为2：
	- 该目录的内容中有一条名为的`.`记录，该记录的 `<i节点编号>` 指向`dirxxx`目录的节点
	- 该目录的父目录的内容中有一条记录，记录的名字`dirxxx`，记录的 `<i节点编号>` 指向`dirxxx`目录的节点
	- 若该目录有子目录。`dirxxx` 的任何子目录的内容有一条名为`..`的记录，该记录的 `<i节点编号>` 指向`dirxxx`目录的节点
	> 因此父目录中的每个子目录都使得父目录的链接计数加 1

4. `link/linkat`函数：创建一个指向现有文件的硬链接

	```
	#include<unistd.h>
	int link(const char *existingpath,const char *newpath);
	int linkat(int efd,const char*existingpath,int nfd,const char *newpath,int flag);
	```

	- 参数：
		- `existingpath`：现有的文件的文件名（新创建的硬链接指向它）
		- `newpath`：新创建的目录项
			- 如果`newpath`已存在，则返回出错
			- 只创建`newpath`中的最后一个分量，路径中的其他部分应当已经存在。
			> 假设 `newpath`为：`/home/aaa/b/c.txt`，则要求 `/home/aaa/b`已经存在，只创建`c.txt`

		对于`linkat`函数：
		- 现有的文件名是通过`efd`和`existingpath`指定。
			- 若`existingpath`是绝对路径，则忽略`efd`
			- 若 `existingpath`是相对路径，则：
				- 若 `efd=AT_FDCWD`，则`existingpath`是相对于当前工作目录来计算
				- 若 `efd`是一个打开的目录文件的文件描述符，则`existingpath`是相对于`efd`对应的目录文件
		- 新建的文件名是通过`nfd`和`newpath`指定。
			- 若`newpath`是绝对路径，则忽略`nfd`
			- 若 `newpath`是相对路径，则：
				- 若 `nfd=AT_FDCWD`，则`newpath`是相对于当前工作目录来计算
				- 若 `nfd`是一个打开的目录文件的文件描述符，则`newpath`是相对于`nfd`对应的目录文件
		- `flag`：当现有文件是符号链接时的行为：
			- `flag=AT_SYMLINK_FOLLOW`：创建符号链接指向的文件的硬链接（跟随行为）
			- `flag=!AT_SYMLINK_FOLLOW`:创建符号链接本身的硬链接（默认行为）

	- 返回值：
		- 成功： 返回 0
		- 失败： 返回 -1

	这两个函数创建新目录项并对链接计数加1。创建新目录项和增加链接计数是一个原子操作。

	另外，大多数操作系统中，只有超级用户才能创建指向一个目录的硬链接，因为这样做很有可能在文件系统中形成循环。

5. `unlink`函数：删除一个现有的目录项

	```
	#include<unistd.h>
	int unlink(const char*pathname);
	int unlinkat(int fd,const char*pathname,int flag);
	```

	- 参数：
		- `pathname`：现有的、待删除的目录项的完整路径名。

		对于`unlinkat`函数：
		- 现有的文件名是通过`fd`和`pathname`指定。
			- 若`pathname`是绝对路径，则忽略`fd`
			- 若 `pathname`是相对路径，则：
				- 若 `fd=AT_FDCWD`，则`pathname`是相对于当前工作目录来计算
				- 若 `fd`是一个打开的目录文件的文件描述符，则`pathname`是相对于`fd`对应的目录文件
		- `flag`：
			- `flag=AT_REMOVEDIR`：可以类似于`rmdir`一样的删除目录
			- `flag=!AT_REMOVEDIR`:与`unlink`执行同样的操作
	- 返回值：
		- 成功： 返回 0
		- 失败： 返回 -1

	为了解除对文件的链接，必须对包含该目录项的目录具有写和执行权限。如果还对该目录设置了粘着位，则对该目录必须具有写权限以及下列三个条件之一：
	- 拥有该文件
	- 拥有该目录
	- 具有超级用户权限

	这两个函数删除目录项并对链接计数减1。创建新目录和增加链接计数是一个原子操作。
	- 如果该文件的硬链接数不为0， 则还可以通过其他链接访问该文件的内容
	- 如果该文件的硬链接数为0，而没有进程打开该文件，则该文件的内容才有被删除
	- 如果该文件的硬链接数为0，但是有进程打开了该文件，则该文件的内容不能被删除。当进程关闭文件时，内核会检查打开该文件的进程个数；当这个数量为0，内核再去检查其链接计数。如果链接计数也是0，则就删除该文件的内容。
		>这个特性常用于创建临时文件，先`open,create`一个文件，然后立即调用`unlink`。这样即使程序崩溃，它所创建的临时文件也不会遗留下来
	- 如果删除目录项出错，则不对该文件做任何更改

	如果`pathname`是个符号链接，则`unlink`删除该符号链接，而不会删除由该符号链接所引用的文件。	
	> 如果仅仅给出符号链接的文件名，没有一个函数可以删除由该符号链接所引用的文件

	如果文件系统支持，超级用户可以调用`unlink`，其参数`pathname`指定一个目录
	> 通常推荐用`rmdir`函数，其语义更加清晰

6. `link/unlink`实例：

	```
	#include<stdio.h>
	#include<unistd.h>
	#include<sys/stat.h>
	#include<fcntl.h>
	#include<string.h>
	#include<errno.h>

	typedef struct stat Stat;
	void print_link_num(const char*path)
	{
    		Stat stat;
    		if(-1==fstatat(AT_FDCWD,path,&stat,0))
    		{
       		 printf("\tfstatat %s error,because %s\n",path,strerror(errno));
    		}else
    		{
        		printf("\t%s link is %d\n",path,stat.st_nlink);
    		}
	}
	void add_link(const char *path,const char *new_path)
	{
    		if(-1==linkat(AT_FDCWD,path,AT_FDCWD,new_path,0))
    		{
       		 printf("\tadd_link %s error,because %s\n",path,strerror(errno));
    		}else
    		{
        		print_link_num(path);
    		}
	}
	void del_link(const char *path)
	{
    		if(-1==unlinkat(AT_FDCWD,path,0))
    		{
        		printf("\tun_link %s error,because %s\n",path,strerror(errno));
    		}else
    		{
       		 print_link_num(path);
    		}
	}

	int main(int argc, char *argv[])
	{
    		int fd;
    		fd=openat(AT_FDCWD,"test",O_CREAT|O_RDWR,S_IRWXU);
    		if (-1==fd) return;
    		close(fd);

    		printf("The original link num\n");
    		print_link_num("test");  // link_num=1
    		printf("Add link\n");
    		add_link("test","new_test");// link_num=2
    		printf("\t The new file link:\n\t");
    		print_link_num("new_test");
   		 printf("Del new file link\n");
   		 del_link("new_test"); // link_num=1
    		printf("\tThe original file link\n\t");
    		print_link_num("test");
    		printf("Del original file link\n");
    		del_link("test"); // link_num=0
    		// test link is 0
    		printf("Del after he original file link is 0:\n");
    		del_link("test");
    		return 0;
	}
	```
	  ![link_unlink](../imgs/file_dir/link_unlink.JPG) 

	可以看到：
	- `test`和`new_test`这两个文件共享一个 i 结点。因此该节点的 硬链接数为2
	- 一旦删除 `new_test`，则对`new_test`执行 `fstatat`失败（因为已经被`unlink`）。同时`test`的硬链接数为1
	- 一旦`test`也被删除，则 `i`节点被释放。执行`unlink`失败。

7. `remove`函数：解除对一个目录或者文件的链接。

	```
	#include<stdio.h>
	int remove(const char *pathname);
	```
	- 参数
		- `pathname`：文件名或者目录名
	- 返回值：
		- 成功：返回0
		- 失败：返回 -1

	对于文件，`remove`功能与`unlink`相同；对于目录，`remove`功能与`rmdir`相同

8. `rename/renameat`函数：重命名文件或目录

	```
	#inluce<stdio.h>
	int rename(const char*oldname,const char *newname);
	int renameat(int oldfd,const char*oldname,int newfd,const char* newname);
	```

	- 参数：
		- `oldname`：现有的文件名或者目录名
		- `newname`：重命名的名字
			- 如果`oldname`是个文件名，则为该文件或者符号链接重命名。
				- 此时若`newname`已存在：若`newname`是个目录则报错；若`newname`不是个目录：则先将`newname`目录项删除，然后将`oldname`重命名为`newname`
				- 此时若`newname`不存在：则直接将`oldname`重命名为`newname`	
			- 如果`oldname`是个目录名，则为该目录重命名。
				- 此时若`newname`已存在：若`newname`是个目录且该目录是个空目录，则先将它删除，然后`oldname`重命名为`newname`；若`newname`是个目录且该目录不是个空目录，则报错；若`newname`不是个目录，则报错
				- 此时若`newname`不存在：则直接将`oldname`重命名为`newname`
			>`oldname` 不能是 `newname` 的前缀。因为重命名时，需要删除`oldname`
			- 如果`oldname`或者`newname`引用的是符号链接，则处理的是符号链接本身，而不是它引用的文件
			- 不能对`.`和`..`重命名。即`.`和`..`不能出现在`oldname`和`newname`的最后部分
			- 若`newname`和`oldname`引用同一个文件，则函数不作任何更改而成功返回

		对于`renameat`函数：
		- 现有的文件名或目录名是通过`oldfd`和`oldname`指定。
			- 若`oldname`是绝对路径，则忽略`oldfd`
			- 若 `oldname`是相对路径，则：
				- 若 `oldfd=AT_FDCWD`，则`oldname`是相对于当前工作目录来计算
				- 若 `oldfd`是一个打开的目录文件的文件描述符，则`oldname`是相对于`oldfd`对应的目录文件
		- 重命名的文件名或目录名是通过`newfd`和`newname`指定。
			- 若`newname`是绝对路径，则忽略`newfd`
			- 若 `newname`是相对路径，则：
				- 若 `newfd=AT_FDCWD`，则`newname`是相对于当前工作目录来计算
				- 若 `newfd`是一个打开的目录文件的文件描述符，则`newname`是相对于`newfd`对应的目录文件
		- `flag`：当现有文件是符号链接时的行为：
			- `flag=AT_SYMLINK_FOLLOW`：创建符号链接指向的文件的硬链接（跟随行为）
			- `flag=!AT_SYMLINK_FOLLOW`:创建符号链接本身的硬链接（默认行为）

	- 返回值：
		- 成功： 返回 0
		- 失败： 返回 -1

	对于包含`oldname`以及`newname`的目录，调用进程必须具有写和执行的权限，因为将同时更改这两个目录。

9. `symlink/symlinkat`函数：创建一个符号链接

	```
	#include<unistd.h>
	int symlink(const char*actualpath,const char *sympath);
	int symlinkat(const char*actualpath,int fd,const char*sympath);
	```

	- 参数：
		- `actualpath`：符号链接要指向的文件或者目录（可能尚不存在）
		- `sympath`：符号链接的名字
		> 二者不要求位于同一个文件系统中


		对于`symlinkat`函数：
		- 符号链接的名字是通过`fd`和`sympath`指定。
			- 若`sympath`是绝对路径，则忽略`fd`
			- 若 `sympath`是相对路径，则：
				- 若 `fd=AT_FDCWD`，则`sympath`是相对于当前工作目录来计算
				- 若 `fd`是一个打开的目录文件的文件描述符，则`sympath`是相对于`fd`对应的目录文件

	- 返回值：
		- 成功： 返回 0
		- 失败： 返回 -1

10. `readlink/readlinkat`函数：打开符号链接本身
	> `open`函数是跟随链接的，即打开符号链接指向的文件

	```
	#include<unistd.h>
	ssize_t readlink(const char *restrict pathname,char *restrict buf,size_t bufsize);
	ssize_t readlinkat(int fd, const char* restrict pathname,char *restrict buf,
		size_t bufsize);
	```
	- 参数：
		- `pathname`：符号链接的名字
		- `buf`：存放符号链接内容的缓冲区
		- `bufsize`：期望读入缓冲区的字节数

		对于`readlinkat`函数：

		- 符号链接的名字是通过`fd`和`pathname`指定。
			- 若`pathname`是绝对路径，则忽略`fd`
			- 若 `pathname`是相对路径，则：
				- 若 `fd=AT_FDCWD`，则`pathname`是相对于当前工作目录来计算
				- 若 `fd`是一个打开的目录文件的文件描述符，则`pathname`是相对于`fd`对应的目录文件

	- 返回值：
		- 成功： 返回实际上读取的字节数
		- 失败： 返回 -1

	`readlink`和`readlinkat`函数组合了`open、read、close`函数的所有操作。

	注意：读入`buf`中的符号链接的内容，并不是以`null`字节终止。
	> 以`null`字节终止的是内存中的字符串这种数据结构。而符号链接文件的内容是简单的字符序列，并不是字符串。

11. 符号链接示例：

	```
	#include <stdio.h>
	#include<unistd.h>
	#include<sys/stat.h>
	#include<string.h>
	#include<errno.h>
	#include<fcntl.h>

	typedef struct stat Stat;

	void test_file_type(const char* file_name)
            {
                Stat _stat;
                if(-1==stat(file_name,&_stat))
                {
                    printf("test_file_type file %s fail,because of %s
	\n",file_name,strerror(errno));
                    return;
                }
                printf("%s file type is:",file_name);
                if(S_ISLNK(_stat.st_mode))
                     printf("link file,  ") ;
                if(S_ISREG(_stat.st_mode))
                    printf(" regular file,  ") ;
                printf("\n");
            }
	void creat_file(const char* file_name)
	{
    	int fd;
    	fd=open(file_name,O_CREAT|O_RDWR,S_IRWXU);
    	if(-1==fd)
    	{
        	printf("creat file %s fail,because of %s\n",file_name,strerror(errno));
    	}
    	else{
        	close(fd);
    	}
	}
	int  creat_symlink(const char* actual_name,const char* sym_name)
	{
    	int ok;
    	ok=symlink(actual_name,sym_name);
    	if(-1==ok)
    	{
        	printf("creat symlink %s fail,because of %s\n",sym_name,strerror(errno));
    	}
    	return ok;
	}
	void read_symlink(const char* sym_name)
	{
    	char buffer[2048];
    	int len,i;
    	len=readlink(sym_name,&buffer,2048);
    	if(-1==len)
    	{
       		 printf("read symlink %s fail,because of %s\n",sym_name,strerror(errno));
   		}else
    	{
        	printf("length <%d>, content:",len);
        	for(i=0;i<len;i++)
        	{
            	printf("%c",buffer[i]);
        	}
        	printf("\n");
    	}
	}

	int main(int argc, char *argv[])
	{

    	creat_file("/home/huaxz1986/test");
    	test_file_type("/home/huaxz1986/test");
    	creat_symlink("/home/huaxz1986/test","/home/huaxz1986/sym_test");
    	test_file_type("/home/huaxz1986/sym_test");
    	read_symlink("/home/huaxz1986/sym_test");
	}

	```

	  ![symlink](../imgs/file_dir/symlink.JPG) 

	可以看到：
	- 符号链接文件的内容就是它链接到的那个文件的绝对路径名，其中路径名字符序列不包含 `null`字节
	- 在 `ubuntu 16.04`中，经多次测试，符号链接文件和普通文件的 `st_mode`完全相同。

## 六、修改文件的时间

1. 文件的时间：在`stat`结构中存放着文件的三个时间：
	- `st_atim`：文件数据的最后访问时间
	- `st_mtim`：文件数据的最后修改时间
	- `st_ctim`： i 节点状态的最后更改时间

	关于这三个时间：
	- 有很多操作，比如修改文件权限，修改文件的所有者等操作，他们只修改 i 节点状态（只影响`st_ctim`），但是并不修改文件数据，也并不访问文件数据
	- 系统并不维护对 `i` 节点的最后访问时间。因此对于 `access`函数和 `stat`函数，他们并不修改这三个时间中的任何一个
	- 创建一个文件不仅影响了文件本身的这三个时间，也会影响该文件目录的这三个时间

2. `futimens/utimensat/utimes`函数：修改文件的访问和修改时间

	```
	#include<sys/stat.h>
	int futimens(int fd,const struct timespec times[2]);
	int utimensat(int fd,const char*path,const struct timespec times[2],int flag);
	#include<sys/time.h>
	int utimes(const char*pathname,const struct timeval times[2]);
	```

	- 参数：

		对于  `futimens`和 `utimensat`函数：
		- `times`：指向待修改文件的指定的文件数据访问和文件数据修改时间的指针。
			> 对于C语言，参数中的数组自动转换为指向数组的指针

			- 这两个时间是日历时间，是自 1970:01:01--00:00:00 以来经历的秒数。不足秒的部分用纳秒表示
			- 数组的第一个元素指定 `st_atim`；数组的第二个元素指定 `st_ctim`
			- `times`可以按照下列四种方式之一指定：
				- `times`为空指针： 则将文件的数据访问时间和文件数据修改时间设置为当前时间
				>  此时要求进程的有效用户ID等于该文件所有者的ID；或者进程对该文件有写权限；或者进程是个超级用户进程
				- `times`参数是指向`timespec`数组的指针：
					- 若数组的任何一个元素的`tv_nsec`字段为 `UTIME_NOW`，则相应的时间戳就设置为当前时间，忽略相应的`tv_sec`字段
					> 此时要求进程的有效用户ID等于该文件所有者的ID；或者进程对该文件有写权限；或者进程是个超级用户进程
					- 若数组的任何一个元素的`tv_nsec`字段为 `UTIME_OMIT`，则相应的时间戳保持不变，忽略相应的`tv_sec`字段
						>若两个时间戳都忽略，则不需要任何权限限制
					- 若数组的任何一个元素的`tv_nsec`字段为不是上面的两种之一，则相应的时间戳就设置为相应的`tv_sec`和`tv_nsec`字段
						> 此时要求进程的有效用户ID等于该文件所有者的ID；或者进程是个超级用户进程（对文件只有写权限是不够的）

		对于 `utimes`函数：
		- `pathname`：文件的路径名
		- `times`：指向`timeval`数组的指针。 `timeval`结构用秒和微秒表示。
	
			```
			struct timeval{
			time_t tv_sec;//秒
			long tv_usec; //微秒
			```

		对于 `futimens`函数：
		- `fd`：待修改文件的打开的文件描述符

		对于 `utimensat`函数：
		- 待打开文件的名字是通过`fd`和`path`指定。
			- 若`path`是绝对路径，则忽略`fd`
			- 若 `path`是相对路径，则：
				- 若 `fd=AT_FDCWD`，则`path`是相对于当前工作目录来计算
				- 若 `fd`是一个打开的目录文件的文件描述符，则`path`是相对于`fd`对应的目录文件
		- `flag`：若待修改的文件是符号链接
			- 如果为`!AT_SYMLINK_FOLLOW`，则符号链接本身的时间就会被修改
			- 默认情况下，修改的是符号链接指向的文件的时间（跟随行为）

	- 返回值：
		- 成功： 返回 0
		- 失败： 返回 -1

	我们不能对`st_ctim`（i节点最后被修改时间）指定一个值。这个时间是被自动更新的。

3. 示例：

	```
	#include <stdio.h>
	#include<sys/stat.h>
	#include<string.h>
	#include<errno.h>
	#include<unistd.h>
	#include<fcntl.h>
	typedef struct stat Stat;
	typedef struct timespec Timespec;
	void print_time(const char*path)
	{
    	Stat buffer;
    	if(-1==stat(path,&buffer))
    	{
        	printf("stat file <%s> error,because %s",path,strerror(errno));
    	}else
    	{
        	printf("\t%s time:\n",path);
        	printf("\t\tdata last access time:<%d s,%d ns
	>\n",buffer.st_atim.tv_sec,buffer.st_atim.tv_nsec);
        	printf("\t\tdata last modify time:<%d s,%d ns>	
	\n",buffer.st_mtim.tv_sec,buffer.st_mtim.tv_nsec);
        	printf("\t\tinfo last access time:<%d s,%d ns
	>\n",buffer.st_ctim.tv_sec,buffer.st_ctim.tv_nsec);
    	}
	}
	void creat_file(const char* file_name)
	{
    	int fd;
    	fd=open(file_name,O_CREAT|O_RDWR,S_IRWXU);
    	if(-1==fd)
    	{
       	 printf("creat file %s fail,because of %s\n",file_name,strerror(errno));
    	}
    	else{
        	close(fd);
    	}
	}
	void set_time(const char* file_name,Timespec  time[2])
	{
    	if(utimensat(AT_FDCWD,file_name,time,0)==-1)
    	{
        	printf("utimensat file <%s> error,because %s",file_name,strerror(errno));
    	}else
    	{
        	print_time(file_name);
    	}
	}

	int main(int argc, char *argv[])
	{
    	Timespec times[2];
 	  	times[0].tv_nsec=10;
    	times[1].tv_sec=10;
    	times[1].tv_nsec=10;
    	printf("Create file:\n");
    	creat_file("/home/huaxz1986/test_time");
    	print_time("/home/huaxz1986/test_time");
    	sleep(2);
    	printf("Access not modify time:\n");
    	access("/home/huaxz1986/test_time",F_OK);
    	print_time("/home/huaxz1986/test_time");
    	sleep(2);
    	printf("Chmod only modify st_ctime:\n");
    	chmod("/home/huaxz1986/test_time",S_IRUSR|S_IWUSR);
    	print_time("/home/huaxz1986/test_time");
    	sleep(2);
    	printf("Set data access time , data modify time to now:");
    	set_time("/home/huaxz1986/test_time",NULL);
    	sleep(2);
    	printf("Set data access time , data modify time  ");
    	set_time("/home/huaxz1986/test_time",times);
    	return 0;
	}
	```

	  ![utimes](../imgs/file_dir/utimes.JPG) 	
	可以看到：
	- `st_ctim`是由系统自动维护的，程序员无法手动指定

## 七、目录操作

1. `mkdir/mkdirat`函数创建一个空目录：

	```
	#include<sys/stat.h>
	int mkdir(const char*pathname,mode_t mode);
	int mkdirat(int fd,const char *pathname,mode_t mode);
	```

	- 参数：
		- `pathname`:被创建目录的名字
		- `mode`:被创建目录的权限

		对于 `mkdirat`，被创建目录的名字是由`fd`和`pathname`共同决定的。
		- 若`pathname`是绝对路径，则忽略`fd`
		- 若 `pathname`是相对路径，则：
			- 若 `fd=AT_FDCWD`，则`pathname`是相对于当前工作目录来计算
			- 若 `fd`是一个打开的目录文件的文件描述符，则`pathname`是相对于`fd`对应的目录文件

	- 返回值：
		- 成功： 返回0
		- 失败： 返回 -1

	注意：
	- 他们创建的目录是空目录。
	- 对于目录，通常至少要设置一个执行权限位，以允许访问该目录中的文件名

2. `rmdir`函数：删除一个空目录

	```
	#include<unistd.h>
	int rmdir(const char *pathname);
	```

	- 参数：
		- `pathname`：待删除的空目录的名字

	- 返回值：
		- 成功： 返回0
		- 失败： 返回 -1

	如果调用此函数使得目录的链接计数为0时：	
	- 如果此时没有其他进程打开该目录，则释放由此目录占用的空间。
	- 如果此时有一个或者多个进程打开此目录，则在此函数返回时删除最后一个链接以及 `.`和`..`项，直到最后一个打开该目录的进程关闭该目录时此目录才真正被释放。
		- 此时，在此目录中不能再创建新文件。

3. 读、写目录：对于某个目录具有访问权限的任何用户都可以读该目录。但是为了防止文件系统产生混乱，只有内核才能写目录。
	> 一个目录的写权限和执行权限位决定了在该目录中能否创建新文件以及删除文件，它们并不能写目录本身

	```
	#include<dirent.h>
	DIR *opendir(const char *pathname);
	DIR *fdopendir(int fd);
	struct dirent *readdir(DIR *dp);
	void rewinddir(DIR *dp);
	int closedir(DIR *dp);
	long telldir(DIR *dp);
	void seekdir(DIR *dp,long loc);
	```

	各个函数：
	- `opendir`：打开目录。
		- 参数：`pathname`：目录的名字
		- 返回值：成功返回目录指针；失败返回 `NULL`
	- `fdopendir`：打开目录。
		- 参数：`fd`：目录文件的文件描述符
		- 返回值：成功返回目录指针；失败返回 `NULL`
	- `readdir`：读取目录
		- 参数： `dp`：目录指针
		- 返回值： 成功则返回目录项的指针；失败返回 `NULL`
	- `rewinddir`:将目录的文件偏移量清零（这样下次读取就是从头开始）
		- 参数：`dp`：目录指针
	- `closedir`：关闭目录。
		- 参数：`dp`：目录指针
		- 返回值：成功返回 0 ；失败返回 -1
	- `telldir`：返回目录的文件偏移量
		- 参数：`dp`：目录指针
		- 返回值：成功返回目录的文件偏移量 ；失败返回 -1
	- `seekdir`：设置目录的当前位置
		- 参数：`dp`：目录指针；`loc`：要设定的文件偏移量

	对于 `DIR`结构，它是一个内部结构。起作用类似于 `FILE`结构。
	对于`dirent`结构，它是定义在`<dirent.h>`头文件中。其与具体操作系统相关。但是它至少定义了两个成员：

	```
	struct dirent{
	ino_t d_ino; // i 节点编号
	char d_name[];// 以 null 结尾的文件名字符串
	}
	```
	> `d_name`项的大小并没有指定，但必须保证它能包含至少 `NAME_MAX`个字节（不包含终止`null`字节）

	目录中各目录项的顺序与操作系统有关。它们通常不按照字母顺序排列

4. 当前工作目录：每个进程都有一个当前工作目录。此目录是搜索所有相对路径名的起点。
	> 当前工作目录是本进程的一个属性

	与当前工作目录相关的有三个函数：

	```
	#include<unistd.h>
	int chdir(const char *pathname);
	int fchdir(int fd);
	char *getcwd(char *buf,size_t size);
	```

	各个函数：
	- `chdir`：更改当前工作目录。
		- 参数：`pathname`：将该目录作为当前工作目录
		- 返回值：成功返回 0 ；失败返回 -1
	- `fchdir`：更改当前工作目录。
		- 参数：`fd`：将该 `fd` 文件描述符对应的目录作为当前工作目录
		- 返回值：成功返回 0 ；失败返回 -1
	- `getcwd`：返回当前工作目录的名字
		- 参数： `buf`：缓冲区地址；`size`：缓冲区长度。这两个参数决定了当前工作目录名字字符串存放的位置。
		> 缓冲区必须足够长以容纳绝对路径名加上一个终止`null`字节。否则返回出错。
		- 返回值： 成功则返回 `buf`；失败返回 `NULL`

5. 示例

	```
	#include <stdio.h>
	#include<unistd.h>
	#include<string.h>
	#include<errno.h>
	#include<dirent.h>S
	typedef struct dirent Dirent;
	void print_current_work_dir()
	{
    	char buffer[1024];
    	if(getcwd(buffer,1024)==NULL)
    	{
        	printf("\t getcwd failed,because:%s\n",strerror(errno));
    	}else
    	{
       	 printf("\t current work dir is :%s\n",buffer);
    	}
	}
	void change_current_work_dir(const char*path)
	{
    	if(chdir(path)==-1)
    	{
        	printf("change current work dir to %s failed,because:%s\n"
	,path,strerror(errno));
    	}else
    	{
        	print_current_work_dir();
    	}
	}
	void list_dir(const char *path)
	{
   	 DIR * dir;
    	Dirent * dir_ent;
    	dir=opendir(path);
    	if(dir==NULL)
    	{
        	printf("\t open dir %s  failed,because:%s\n",path,strerror(errno));
        	return;
    	}
    	printf("%s contents is :\n",path);
    	while((dir_ent=readdir(dir)) !=NULL)
    	{
       	 printf("\tid:<%d>, file_name :<%s>\n",dir_ent->d_ino,dir_ent->d_name);
    	}
    	closedir(dir);
	}

	int main(int argc, char *argv[])
	{
   	 printf("Current work dir:\n");
   	 print_current_work_dir();
    	printf("Expected change current work dir to /home/huaxz1986\n");
    	change_current_work_dir("/home/huaxz1986");
    	list_dir("/home/huaxz1986");
    	return 0;
	}
	```

	  ![dir_function](../imgs/file_dir/dir_function.JPG) 