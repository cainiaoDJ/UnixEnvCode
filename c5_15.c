//
// Created by 杨慧文 on 2020/5/15.
//

// 跟书中的例子输出结果不一致。


#include "apue.h"

#define BSZ 48

int main() {
    FILE *fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) {
        err_sys("fmemopen failed");
    }
    printf("initial buffer contents: %s\n", buf);
    fprintf(fp, "hello world");
    printf("before fflush: %s\n", buf);
    fflush(fp);
    printf("after fflush: %s\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));

    memset(buf, 'b', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello world");
    // 重定位流(数据流/文件)上的文件内部位置指针[重置指针位置]
    fseek(fp, 0, SEEK_SET);
    printf("after fseek: %s\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));

    memset(buf, 'c', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello world");
    fclose(fp);
    printf("after fclose: %s\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));
    return 0;

}