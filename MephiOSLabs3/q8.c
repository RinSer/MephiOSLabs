#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Включить в порожденный процесс системный вызов signal, 
переопределяющий стандартную реакцию на сигнал 
(для внешнего цикла установить в функции максимальное значение параметра цикла). 
Что изменится?
*/

void childReaper8(int);
void childHandler(int);

int q8()
{
    printf("=== question 8 start ===\n\n");

    int signal2child = SIGUSR1;

    int pid = fork();

    if (pid < 0) return catch ();

    if (pid == 0)
    {
        signal(signal2child, childHandler);

        int iterNum = 1000001;
        for (int i = 0; i < iterNum; i++)
        {
            printf("Child iteration number %d\n", i);
        }
    }
    else
    {
        signal(SIGCHLD, childReaper8);

        kill(pid, signal2child);

        pause();
    }

    return 0;
}

void childReaper8(int signum) {
    int status;
    int cpid = wait(&status);
    printf("Child with PID %d has ended with status %d\n", cpid, status);
    printf("\n==== question 8 end ====\n");
    exit(0);
}