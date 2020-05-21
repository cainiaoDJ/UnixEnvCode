//
// Created by 杨慧文 on 2020/5/11.
//

#include "apue.h"
#include "errno.h"

void make_temp(char *template);

int main(void) {
    // 存在栈上
    char good_template[] = "/tmp/dirXXXXXX";
    // bad_template只是一个指针，指向一个常量。这个指针无法指向地址无法被修改
    char *bad_template = "/tmp/dirXXXXXX";

    printf("trying to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
    exit(0);
}

void make_temp(char *template) {
    int fd;
    struct stat sbuf;
    if ((fd = mkstemp(template)) < 0) {
        err_sys("can't create temp file");
    }

    printf("temp name = %s\n", template);
    close(fd);

    if (stat(template, &sbuf) < 0) {
        if (errno == ENOENT) {
            printf("file doesn't exists\n");
        } else {
            err_sys("stat failed");
        }
    } else {
        printf("file exists\n");
        unlink(template);
    }

}