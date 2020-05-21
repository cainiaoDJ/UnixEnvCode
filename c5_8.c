//
// Created by 杨慧文 on 2020/5/7.
//

#include "apue.h"

int main(void) {
    int c;
    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            err_sys("output error");
        }
    }
    if (ferror(stdin)) {
        err_sys("input error");
    }
    exit(0);
}