# 文件IO：不带缓冲的IO

1.**文件描述符**：一个非负整数，范围是`0~OPEN_MAX-1`。内核用它来标识进程正在访问的文件。当进程创建时，默认为它打开了3个文件描述符，它们都链接向终端：

- 0： 标准输入
- 1： 标准输出
- 2： 标准错误输出

通常我们应该使用`STDIN_FILENO`，`STDOUT_FILENO`和 `STDERR_FILENO`来替代这三个幻数，从而提高可读性。这三个常量位于`<unistd.h>`中。

2.open和openat函数：

```
#include<fcntl.h>
int open(const char* path,int oflag,.../*mode_t mode*/);
int openat(int fd,const char*path,int oflag,.../*mode_t mode */);
```

参数：

- `path`:要打开或者创建文件的名字
- `oflag`：用于指定函数的操作行为：
	- `O_RDONLY`常量：文件只读打开
	- `O_WRONLY`常量：文件只写打开
	- `O_RDWR`常量：文件读、写打开
	- `O_EXEC`常量：