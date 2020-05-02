#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
Написать программу, позволяющую использовать sigaction для реализации примера синхронизации процессов. 
Выполнить эту программу и объяснить ее поведение. Использовать sigsuspend и sigprocmask.
*/

void onSignal11(int);

int q11()
{
    printf("=== question 11 start ===\n\n");

    struct sigaction newAction;
    if (sigfillset(&newAction.sa_mask) < 0)
        return catch ();
    newAction.sa_handler = onSignal11;
    newAction.sa_flags = 0;

    if (sigaction(SIGINT, &newAction, NULL) < 0)
        return catch ();

    pause();

    return 0;
}

void onSignal11(int signum) {
    printf("Sleeping on signal %d\n", signum);

    sleep(5);

    printf("\n==== question 11 end ====\n");

    exit(0);
}