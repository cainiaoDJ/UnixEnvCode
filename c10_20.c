#include "apue.h"
#include <setjmp.h>
#include <time.h>

// 测试步骤
// nohup ./a.out &
// kill -USR1 pid
// cat nohup.out

static void sig_usr1(int);
static void sig_alrm(int);
// 这里变量名换掉了，源码使用的是jmp_buf。已经被定义为一种类型了。
static sigjmp_buf sjmp_buf;
static volatile sig_atomic_t canjump;

int main(void)
{
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
    {
        err_sys("signal(SIG_USER1) error");
    }

    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    {
        err_sys("signal(SIGALRM) error");
    }
    pr_mask("starting main: ");

    if (sigsetjmp(sjmp_buf, 1))
    {
        pr_mask("ending main: ");
        exit(0);
    }

    canjump = 1;

    for (;;)
    {
        pause();
    }
}

static void sig_usr1(int signo)
{
    time_t starttime;
    if (canjump == 0)
    {
        return;
    }

    pr_mask("starting sig_usr1: ");

    alarm(3);
    starttime = time(NULL);

    for (;;)
    {
        if (time(NULL) > starttime + 5)
        {
            break;
        }
    }

    pr_mask("finishing sig_usr1: ");

    canjump = 0;
    siglongjmp(sjmp_buf, 1);
}

static void sig_alrm(int signo)
{
    pr_mask("in sig_alrm");
}