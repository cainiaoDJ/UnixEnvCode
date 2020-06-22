//
// Created by 杨慧文 on 2020/6/22.
//

/**
 * SIGHUP是unix中进程组织结构为 session 包含一个前台进程组及一个或多个后台进程组，一个进程组包含多个进程。
 * SIGTSTP与SIGSTOP都是使进程暂停（都使用SIGCONT让进程重新激活）。唯一的区别是SIGSTOP不可以捕获。
 * STDIN_FILENO：接收键盘的输入
 */

#include "apue.h"
#include <errno.h>

static void sig_hup(int signo) {
    printf("SIGHUP received, pid = %ld \n", (long) getpid());
}

static void pr_ids(char *name) {
    // 自己的id，父进程id，进程组id，前台进程组id
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld \n",
           name, (long) getpid(), (long) getppid(), (long) getpgrp(),
           (long) tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main(void) {
    char c;
    pid_t pid;

    pr_ids("parent");
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        sleep(5);
    } else {
        pr_ids("child");
        signal(SIGHUP, sig_hup);
        kill(getpid(), SIGTSTP);
        pr_ids("child");

        if (read(STDIN_FILENO, &c, 1) != 1) {
            printf("read error %d on controlling TTY\n", errno);
        }
    }
    exit(0);
}