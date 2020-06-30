#include "apue.h"

//set nozero by sig handler
static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

// one signal handler for SIGUSR1 and SIGUSR2
static void sig_usr(int signo)
{
    sigflag = 1;
}

void TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        err_sys("signal(SIGUSR1) error");
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        err_sys("signal(SIGUSR2) error");
    }

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    // block SIGUSR1 and SIGUSR2, and save current signal mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }
}

void TELL_PARENT(pid_t pid)
{
    // tell parent we are done
    kill(pid, SIGUSR2);
}

void WAIT_PARENT(void)
{
    while (sigflag == 0)
    {
        // wait for parent
        sigsuspend(&zeromask);
    }
    sigflag = 0;

    // reset signal mask to original value
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }
}

void TELL_CHILD(pid_t pid)
{
    // tell child we are done
    kill(pid, SIGUSR1);
}

void WAIT_CHILD(void)
{
    while (sigflag == 0)
    {
        // and wait for child
        sigsuspend(&zeromask);
    }
    sigflag = 0;

    //reset signal mask to original value
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }
}