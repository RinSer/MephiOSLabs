#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
Модифицировать программу п.1 так, чтобы вместо signal использовать sigaction.
*/

void onSignal2(int);

struct sigaction defaultAction;

int q2()
{
    printf("=== question 2 start ===\n\n");

    struct sigaction newAction;
    if (sigemptyset(&newAction.sa_mask) < 0)
        return catch();
    newAction.sa_handler = onSignal2;
    newAction.sa_flags = 0;

    if (sigaction(SIGINT, &newAction, &defaultAction) < 0)
        return catch();

    for (;;);

    return 0;
}

void onSignal2(int signum) {
    printf("Exiting on signal %d\n", signum);

    sigaction(signum, &defaultAction, NULL);

    printf("\n==== question 2 end ====\n");

    raise(signum);
}