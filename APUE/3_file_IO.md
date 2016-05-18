<!--
    作者：华校专
    email: huaxz1986@163.com
**  本文档可用于个人学习目的，不得用于商业目的  **
-->
# 文件IO

1. **文件描述符**：一个非负整数。内核用它来标识进程正在访问的文件。当进程创建时，默认为它打开了3个文件描述符，它们都链接向终端：
	- 0： 标准输入
	- 1： 标准输出
	- 2： 标准错误输出

2. 在`<unistd.h>`头文件中，定义了三个常量：
	- `STDIN_FILENO`：指定了标准输入的文件描述符
	- `STDOUT_FILENO`:指定了标准输出的文件描述符
	- `STDERR_FILENO`：指定了标准错误输出的文件描述符
	> 在`POSIX`标准中，这些常量分别为 0、1、2

2. 不带缓冲的 IO：`open、read、write、lseek、close`等。
	- 这些系统调用不是 `ISO C`的组成部分
	- 这些函数由操作系统内核调用并执行

3. 标准IO：标准IO函数为那些不带缓冲的IO函数提供了一个带缓冲的接口。使用标准IO函数还简化了对输入行的处理。如`fgets`、`printf`等。
> 标准IO库在是通过不带缓冲的IO实现的。


4. `open()`函数：打开文件

```
#include <fcntl.h>
int open(const char* pathname,int oflag,.../*mode_t mode*/);
```

`open()`函数打开文件。如果打开成功则返回文件描述符，出错则返回 -1。

> `open()`返回的一定是最小的未使用的文件描述符值。

5. `create()`函数：创建并打开文件

```
#include<fcntl.h>
int create(const char* pathname,mode_t mode);
```

