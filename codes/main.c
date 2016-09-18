/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   main 源文件
 *
 */
#include <stdio.h>
#include<errno.h>
#include<unistd.h>
#include"src/header.h"
#include"src/1_UNIX_Introduction/strerror_perror.h"
#include"src/2_UNIX_Standard/sysconf_pathconf.h"
#include"src/3_File_IO/open_creat.h"
#include"src/3_File_IO/lseek_read_write.h"
#include"src/3_File_IO/pread_pwrite.h"
#include"src/3_File_IO/dup_dup2.h"
#include"src/3_File_IO/fcntl_.h"
#include"src/4_File_Dir/stat_lstat.h"
#include"src/4_File_Dir/access_umask.h"
#include"src/4_File_Dir/chmod_chown.h"
#include"src/4_File_Dir/truncate_size.h"
#include"src/4_File_Dir/link_unlink.h"
#include"src/4_File_Dir/symlink_readlink.h"
#include"src/4_File_Dir/utimes_.h"
#include"src/4_File_Dir/dir_operations.h"
#include"src/5_Std_IO/fopen_fclose.h"
#include"src/5_Std_IO/get_put_seek.h"
#include"src/5_Std_IO/printf_scanf.h"
#include"src/5_Std_IO/tmpnam_mkdtemp.h"
#include"src/5_Std_IO/fmemopen_.h"
#include"src/6_System_Info/system_file.h"
#include"src/6_System_Info/times_.h"
#include"src/7_Progress_Env/exit_atexit.h"
#include"src/7_Progress_Env/malloc_realloc.h"
#include"src/7_Progress_Env/getenv_setenv.h"
#include"src/7_Progress_Env/setjmp_longjmp.h"
#include"src/7_Progress_Env/getrlimit_setrlimit.h"
#include"src/8_Progress_Control/progress_id.h"
#include"src/8_Progress_Control/fork_.h"
#include"src/8_Progress_Control/vfork_.h"
#include"src/8_Progress_Control/wait_waitpid.h"
#include"src/8_Progress_Control/exec_.h"
#include"src/8_Progress_Control/system_.h"
#include"src/8_Progress_Control/setuid_seteuid.h"
#include"src/8_Progress_Control/progress_times_.h"
#include"src/8_Progress_Control/getpriority_setpriority.h"
#include"src/9_Progress_Relation/getpgrp_getpgid.h"
#include"src/9_Progress_Relation/setpgid_.h"
#include"src/9_Progress_Relation/getsid_setsid.h"
#include"src/9_Progress_Relation/tcgetpgrp_tcsetpgrp.h"
#include"src/10_Signal/kill_raise.h"
#include"src/10_Signal/alarm_.h"
#include"src/10_Signal/pause_.h"
#include"src/10_Signal/sigprocmask_sigset.h"
#include"src/10_Signal/sigpending_.h"
#include"src/10_Signal/sigaction_.h"
#include"src/10_Signal/sigsetjmp_siglongjmp.h"
#include"src/10_Signal/sigsuspend_.h"
#include"src/10_Signal/abort_.h"
#include"src/10_Signal/sleep_nanosleep.h"
/*!
 * \brief main : main 函数
 * \return : 0
 */
int main(void)
{
//    //******* 第一章 ***********//
//    test_strerror_perror();
//    //******** 第二章 *********//
//    test_sycconf_pathconf();
//    //******** 第三章 *********//
//    test_open_creat();
//    test_lseek_read_write();
//    test_pread_pwrite();
//    test_dup_dup2();
//    test_fcntl();
//    //******** 第四章 *********//
//    test_stat_lstat();
//    test_access_umask();
//    test_chmod_chown();
//    test_truncate_size();
//    test_link_unlink();
//    test_symlink_readlink();
//    test_utimes();
//    test_dir_operations();
//    //******** 第五章 *********//
//    test_fopen_fwide_setvbuf();
//    test_get_put_seek();
//    test_printf_scanf();
//    test_tmpnam_mkdtemp();
//    test_memstream();
//    //******** 第六章 *********//
//    test_system_file();
//    test_times();
//    //******** 第七章 *********//
//    test_exit_atexit();
//    test_malloc_realloc();
//    test_getenv_setenv();
//    test_setjmp_longjmp();
//    test_getrlimit_setrlimit();
//    //******** 第八章 *********//
//    test_progress_id();
//    test_fork();
//    test_vfork();
//    test_wait_waitpid();
//    test_exec();
//    test_system();
//    test_setuid_seteuid();
//    test_progress_times();
//    test_getpriority_setpriority();
//    //******** 第九章 *********//
//    test_getpgrp_getpgid();
//    test_setpgid();
//    test_getsid_setsid();
//    test_tcgetpgrp_tcsetpgrp();
//    //******** 第十章 *********//
//    test_kill_raise();
//    test_alarm();
//    test_pause();
//    test_sigprocmask_sigset();
//    test_sigpending();
//    test_sigaction();
//    test_sigsetjmp_siglongjmp();
//    test_sigsuspend();
//    test_abort();
    test_sleep_nanosleep();
    return 0;
}
