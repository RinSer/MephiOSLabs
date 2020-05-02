#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
Изменить реакцию процесса на некоторый сигнал при помощи signal. 
В функции обработчике переустановить реакцию на сигнал на значение по умолчанию. 
Запустить программу и объяснить наблюдаемый результат.
*/

void onSignal(int);

int defaultHandler;

int q1()
{
    printf("=== question 1 start ===\n\n");
    
    defaultHandler = signal(SIGINT, onSignal);

    for (;;);

    return 0;
}

void onSignal(int signum) {
    printf("Exiting on signal %d\n", signum);

    signal(signum, defaultHandler);

    printf("\n==== question 1 end ====\n");

    raise(signum);
}