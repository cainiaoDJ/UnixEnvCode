//
// Created by 杨慧文 on 2020/6/24.
//

#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include "apue.h"

static jmp_buf env_alrm;

unsigned int sleep2(unsigned int);

static void sig_int(int);

static void sig_alrm(int signo) {
    printf("trigger_jump\n");
    longjmp(env_alrm, 1);

}

unsigned int sleep2(unsigned int seconds) {
    if (signal(SIGALRM, sig_alrm) == SIGEMT) {
        printf("run 1\n");
        return (seconds);
    }
    if (setjmp(env_alrm) == 0) {
        printf("run 2： second:%d \n", seconds);
        alarm(seconds);
        pause();
    }
    // 当信号中断触发的时候，会执行这里
    printf("run 3 second:%d \n", seconds);
    return (alarm(0));
}

int main(void) {
    unsigned int unslept;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        err_sys("signal(SIGINT) error");
    }

    unslept = sleep2(5);
    // 最后alarm(0) 会清除闹钟信号
    printf("sleep2 returned: %u\n", unslept);
    exit(0);
}

static void sig_int(int signo) {
    int i, j;
    // volatile不被优化
    volatile int k;

    printf("\nsig_int starting\n");
    for (i = 0; i < 3000000; i++) {
        for (j = 0; j < 40000; j++) {
            k += i * j;
        }
    }
    printf("sig_int finished\n");
}