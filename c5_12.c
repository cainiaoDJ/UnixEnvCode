//
// Created by 杨慧文 on 2020/5/11.
//

#include "apue.h"

int main(void) {
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;
    printf("%s\n", tmpnam(NULL));
    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) {
        err_sys("tmpfile error");
    }

    fputs("one line of output\n", fp);
    // C 库函数 void rewind(FILE *stream) 设置文件位置为给定流 stream 的文件的开头。
    rewind(fp);
    if (fgets(line, sizeof(line), fp) == NULL) {
        err_sys("fgets error");
    }
    fputs(line, stdout);

    exit(0);
}