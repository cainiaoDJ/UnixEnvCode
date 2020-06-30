#include "apue.h"

static void sig_int(int);

int main(void)
{
    sigset_t newmask, oldmask, waitmask;
    pr_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGINT) error");
    }

    // 添加信号集，waitmask里是SIGUSR1，newmask里是SIGINT
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    // block SIGINT and save current signal mask.
    // 添加屏蔽信号，为newmask 与 oldmask并集
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }

    // critical region of code，因为只有SIGINT被加入
    pr_mask("in critical region:");

    // pasue, allowing all signals except SIGUSR1
    // 暂停，等待，当sigsuspend返回的时候，信号屏蔽字被设为之前的值，也就是说不响应USR1
    if (sigsuspend(&waitmask) != -1)
    {
        err_sys("sigsuspend error");
    }

    pr_mask("after return from sigsuspend: ");

    // reset signal mask which unblocks SIGINT.
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }

    // and continue processing
    pr_mask("program exit: ");
    exit(0);
}

static void sig_int(int signo)
{
    pr_mask("\n in sig_int:");
}