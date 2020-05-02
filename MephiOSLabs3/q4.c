#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Создать длительный параллельный процесс 
(в порожденном процессе выполнять вложенные циклы, каждый на 100 или больше итераций, 
и выводить на экран номер итерации для внешнего цикла). 
Дождаться нормального завершения порожденного процесса. 
Посмотреть, какой статус будет передан в родительский процесс.
*/

void childReaper4(int);

int q4()
{
    printf("=== question 4 start ===\n\n");

    int pid = fork();

    if (pid < 0) return catch();

    if (pid == 0)
    {
        int iterNum = 101;
        for (int i = 0; i < iterNum; i++)
            for (int j = 0; j < iterNum; j++)
            {
                printf("Child iteration number %d\n", i);
            }
    }
    else
    {
        signal(SIGCHLD, childReaper4);
        pause();
    }

    return 0;
}

void childReaper4(int signum) {
    int status;
    int cpid = wait(&status);
    printf("Child with PID %d has ended with status %d\n", cpid, status);
    printf("\n==== question 4 end ====\n");
    exit(0);
}