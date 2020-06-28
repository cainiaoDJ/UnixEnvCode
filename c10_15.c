#include "apue.h"
static void sig_quit(int);

int main(void)
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
    {
        err_sys("can't catch SIGQUIT");
    }

    // block sigquit and save current signal mask.
    // 初始化newmask指向的信号集，清除其中所有信号
    sigemptyset(&newmask);

    // 向newmask中加入SIGQUIT. 键盘Ctrl + \ 触发
    sigaddset(&newmask, SIGQUIT);

    // SIG_BLOCK 表示newmask和oldmask的并集
    // SIG_UNBLOCK 表示oldmask和newmask的补集的交集，即newmask放入期望解除阻塞的信号
    // SIG_SETMASK 直接输入，表示替换
    // sigprocmask 返回0成功，-1 出错
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }

    // SIGQUIT here will remain pending
    sleep(5);

    // sigpending函数返回在送往进程的时候被阻塞挂起的信号集合
    if (sigpending(&pendmask) < 0)
    {
        err_sys("sigpending error");
    }

    if (sigismember(&pendmask, SIGQUIT))
    {
        printf("\nSIGQUIT pending\n");
    }

    // restore singal mask which unblocks SIGQUIT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }
    printf("SIGQUIT unblocked \n");

    sleep(5);
    exit(0);
}

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
    {
        err_sys("can't reset SIGQUIT");
    }
}