TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += DBG
SOURCES += main.c \
    src/1_UNIX_Introduction/strerror_perror.c \
    src/2_UNIX_Standard/sysconf_pathconf.c \
    src/3_File_IO/open_creat.c \
    src/3_File_IO/lseek_read_write.c \
    src/3_File_IO/pread_pwrite.c \
    src/3_File_IO/dup_dup2.c \
    src/3_File_IO/fcntl_.c \
    src/4_File_Dir/stat_lstat.c \
    src/4_File_Dir/access_umask.c \
    src/4_File_Dir/chmod_chown.c \
    src/4_File_Dir/truncate_size.c \
    src/4_File_Dir/link_unlink.c \
    src/tools.c \
    src/4_File_Dir/symlink_readlink.c \
    src/4_File_Dir/utimes_.c \
    src/4_File_Dir/dir_operations.c \
    src/5_Std_IO/fopen_fclose.c \
    src/5_Std_IO/get_put_seek.c \
    src/5_Std_IO/printf_scanf.c \
    src/5_Std_IO/tmpnam_mkdtemp.c \
    src/5_Std_IO/fmemopen_.c \
    src/6_System_Info/system_file.c \
    src/6_System_Info/times_.c \
    src/7_Progress_Env/exit_atexit.c \
    src/7_Progress_Env/malloc_realloc.c \
    src/7_Progress_Env/getenv_setenv.c \
    src/7_Progress_Env/setjmp_longjmp.c \
    src/7_Progress_Env/getrlimit_setrlimit.c \
    src/8_Progress_Control/progress_id.c \
    src/8_Progress_Control/fork_.c \
    src/8_Progress_Control/vfork_.c \
    src/8_Progress_Control/wait_waitpid.c \
    src/8_Progress_Control/exec_.c \
    src/8_Progress_Control/system_.c \
    src/8_Progress_Control/setuid_seteuid.c \
    src/8_Progress_Control/progress_times_.c \
    src/8_Progress_Control/getpriority_setpriority.c \
    src/9_Progress_Relation/getpgrp_getpgid.c \
    src/9_Progress_Relation/setpgid_.c \
    src/9_Progress_Relation/getsid_setsid.c \
    src/9_Progress_Relation/tcgetpgrp_tcsetpgrp.c \
    src/10_Signal/kill_raise.c \
    src/10_Signal/alarm_.c \
    src/10_Signal/pause_.c \
    src/10_Signal/sigprocmask_sigset.c \
    src/10_Signal/sigpending_.c \
    src/10_Signal/sigaction_.c \
    src/10_Signal/sigsetjmp_siglongjmp.c \
    src/10_Signal/sigsuspend_.c \
    src/10_Signal/abort_.c \
    src/10_Signal/sleep_nanosleep.c

HEADERS += \
    src/header.h \
    src/1_UNIX_Introduction/strerror_perror.h \
    src/2_UNIX_Standard/sysconf_pathconf.h \
    src/3_File_IO/open_creat.h \
    src/3_File_IO/lseek_read_write.h \
    src/3_File_IO/pread_pwrite.h \
    src/3_File_IO/dup_dup2.h \
    src/3_File_IO/fcntl_.h \
    src/4_File_Dir/stat_lstat.h \
    src/4_File_Dir/access_umask.h \
    src/4_File_Dir/chmod_chown.h \
    src/4_File_Dir/truncate_size.h \
    src/4_File_Dir/link_unlink.h \
    src/tools.h \
    src/4_File_Dir/symlink_readlink.h \
    src/4_File_Dir/utimes_.h \
    src/4_File_Dir/dir_operations.h \
    src/5_Std_IO/fopen_fclose.h \
    src/5_Std_IO/get_put_seek.h \
    src/5_Std_IO/printf_scanf.h \
    src/5_Std_IO/tmpnam_mkdtemp.h \
    src/5_Std_IO/fmemopen_.h \
    src/6_System_Info/system_file.h \
    src/6_System_Info/times_.h \
    src/7_Progress_Env/exit_atexit.h \
    src/7_Progress_Env/malloc_realloc.h \
    src/7_Progress_Env/getenv_setenv.h \
    src/7_Progress_Env/setjmp_longjmp.h \
    src/7_Progress_Env/getrlimit_setrlimit.h \
    src/8_Progress_Control/progress_id.h \
    src/8_Progress_Control/fork_.h \
    src/8_Progress_Control/vfork_.h \
    src/8_Progress_Control/wait_waitpid.h \
    src/8_Progress_Control/exec_.h \
    src/8_Progress_Control/system_.h \
    src/8_Progress_Control/setuid_seteuid.h \
    src/8_Progress_Control/progress_times_.h \
    src/8_Progress_Control/getpriority_setpriority.h \
    src/9_Progress_Relation/getpgrp_getpgid.h \
    src/9_Progress_Relation/setpgid_.h \
    src/9_Progress_Relation/getsid_setsid.h \
    src/9_Progress_Relation/tcgetpgrp_tcsetpgrp.h \
    src/10_Signal/kill_raise.h \
    src/10_Signal/alarm_.h \
    src/10_Signal/pause_.h \
    src/10_Signal/sigprocmask_sigset.h \
    src/10_Signal/sigpending_.h \
    src/10_Signal/sigaction_.h \
    src/10_Signal/sigsetjmp_siglongjmp.h \
    src/10_Signal/sigsuspend_.h \
    src/10_Signal/abort_.h \
    src/10_Signal/sleep_nanosleep.h

DISTFILES +=

