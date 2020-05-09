#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
Написать программу, иллюстрирующую способ блокирования дополнительных сигналов на время работы обработчика сигнала. 
Что произойдет, если во время обработки некоторого сигнала в процесс поступит несколько однотипных заблокированных сигналов.
*/

void onSignal10(int);

int q10()
{
    printf("=== question 10 start ===\n\n");

    struct sigaction newAction;
    if (sigfillset(&newAction.sa_mask) < 0)
        return catch();
    newAction.sa_handler = onSignal10;
    newAction.sa_flags = 0;

    if (sigaction(SIGINT, &newAction, NULL) < 0)
        return catch();

    pause();

    return 0;
}

void onSignal10(int signum) {
    printf("Sleeping on signal %d\n", signum);

    sleep(5);

    printf("\n==== question 10 end ====\n");

    exit(0);
}