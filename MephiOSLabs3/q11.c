#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

/*
Написать программу, позволяющую использовать sigaction для реализации примера синхронизации процессов. 
Выполнить эту программу и объяснить ее поведение. Использовать sigsuspend и sigprocmask.
*/

volatile sig_atomic_t no_interrupt = 1;
void sync_signal(int);

int q11()
{
    printf("=== question 11 start ===\n\n");

    int signal2wait = SIGUSR1;

    int pid = fork();

    if (pid > 0)
    {
        struct sigaction on_signal;
        if (sigfillset(&on_signal.sa_mask) < 0)
            return catch();
        on_signal.sa_handler = sync_signal;
        on_signal.sa_flags = 0;
        if (sigaction(signal2wait, &on_signal, NULL) < 0)
            return catch();

        sigset_t mask;
        /*if (sigfillset(&mask) +
            sigdelset(&mask, signal2wait) < 0)
            return catch();*/
        if (sigprocmask(SIG_BLOCK, NULL, &mask) < 0)
            return catch();

        while (no_interrupt)
            sigsuspend(&mask);
    }
    else 
    {
        for (int i = 1; i < 11; i++)
        {
            printf("Child iteration number %d\n", i);
            sleep(1);
        }
        kill(getppid(), signal2wait);
        exit(0);
    }

    printf("\n==== question 11 end ====\n");

    return 0;
}

void sync_signal(int signum)
{
    printf("Parent proceeds after wait on signal %d\n", signum);
    no_interrupt = 0;
}