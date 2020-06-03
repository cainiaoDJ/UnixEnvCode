//
// Created by 杨慧文 on 2020/6/3.
//

#include "apue.h"

int globvar = 6;
char buf[] = "a write to stdout\n";

int main(void) {
    int var;
    pid_t pid;
    var = 88;
    if (writen(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        err_sys("write error");
    }


    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
    printf("before fork \n");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        globvar++;
        var++;
    } else {
        sleep(5);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
    exit(0);
}