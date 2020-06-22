//
// Created by 杨慧文 on 2020/6/22.
//
/**
 * SIGUSR1/2 用户自定义信号,可用于应用程序
 */

#include "apue.h"

// one handler for both signals
static void sig_usr(int);

int main(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        err_sys("can't catch SIGUSR1");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        err_sys("can't catch SIGUSR2");
    }

    for (;;) {
        pause();
    }
}

static void sig_usr(int signo) {
    if (signo == SIGUSR1) {
        printf("received SIGUSR1 \n");
    } else if (signo == SIGUSR2) {
        printf("received SIGUSR2 \n");
    } else {
        err_dump("received singal: %d\n", signo);
    }
}