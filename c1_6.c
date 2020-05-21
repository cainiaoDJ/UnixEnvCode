//
// Created by 杨慧文 on 2020/5/6.
//

#include "apue.h"
int main(int argc, char *argv[]) {
    printf("hello world from  process ID %ld\n",(long)getpid());
    exit(0);
}