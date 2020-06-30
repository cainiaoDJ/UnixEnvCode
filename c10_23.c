#include "apue.h"

// set nonzero by signal handler
volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
    if (signo == SIGINT)
    {
        printf("\ninterrupt\n");
    }
    else if (signo == SIGQUIT)
    {
        quitflag = 1;
    }
}

int main(void)
{
    sigset_t newmask, oldmask, zeromask;
    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGINT) error");
    }

    if (signal(SIGQUIT, sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGQUIT) error");
    }

    // 初始化信号集，并把SIGQUIT 加入到newmask中
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    // block SIGQUIT and save current signal mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }
    pr_mask("now1: ");
    printf("quitflag = %d\n", quitflag);
    while (quitflag == 0)
    {
        sigsuspend(&zeromask);
    }
    printf("quitflag = %d\n", quitflag);
    pr_mask("now2: ");
    //SIGQUIT has been caught and is now blocked; do whatever;
    quitflag = 0;
    // reset signal mask which unblocks SIGQUIT.
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }
    exit(0);
}