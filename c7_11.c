//
// Created by 杨慧文 on 2020/6/24.
//

#include "apue.h"
#include <setjmp.h>

#define TOK_ADD 5
jmp_buf jmpbuffer;
char *tok_ptr;

void do_line(char *);

void cmd_add(void);

int get_token(void);

int main(void) {
    char line[MAXLINE];
    if (setjmp(jmpbuffer) != 0) {
        printf("error\n");
    }
    while (fgets(line, MAXLINE, stdin) != NULL) {
        do_line(line);
    }
    exit(0);
}

void cmd_add(void) {
    int token;
    token = get_token();
    // 不懂作者的逻辑，这里加的测试代码
    token = -1;
    if (token < 0) {
        longjmp(jmpbuffer, 1);
    }
}

void do_line(char *ptr) {
    int cmd;
    tok_ptr = ptr;
    while ((cmd = get_token()) > 0) {
        switch (cmd) {
            case TOK_ADD:
                cmd_add();
                break;
        }
    }

}


int get_token(void) {
    // 不懂作者的逻辑，这里加的测试代码，源码无返回值
    return TOK_ADD;
}