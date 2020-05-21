//
// Created by 杨慧文 on 2020/5/6.
//

#include "apue.h"
#include "errno.h"

int main(int argc, char *argv[]) {
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]);
    exit(0);
}