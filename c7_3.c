//
// Created by 杨慧文 on 2020/5/21.
//

#include "apue.h"

static void my_exit1(void);

static void my_exit2(void);

// atexit 登记退出处理函数
int main(void) {
    // 登记的时候 也会执行printf
    if (atexit(my_exit2) != 0) {
        err_sys("can't register my_exit2");
    }

    if (atexit(my_exit1) != 0) {
        err_sys("can't register my_exit1");
    }

    if (atexit(my_exit1) != 0) {
        err_sys("can't register my_exit1");
    }

    printf("main is done\n");
    // 调用的时候 输出second ...
    my_exit2();
}

static void my_exit1(void){
    printf("first exit handler \n");
}

static void my_exit2(void){
    printf("second exit handler \n");
}