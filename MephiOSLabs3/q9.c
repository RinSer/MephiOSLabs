#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Включить в порожденный процесс вместо системного вызова kill 
системный вызов alarm с перехватом и без перехвата сигнала. 
Что изменится?
*/

void childReaper9(int);
void childHandler(int);

int q9()
{
    printf("=== question 9 start ===\n\n");

    int signal2child = SIGALRM;

    int pid = fork();

    if (pid < 0) return catch ();

    if (pid == 0)
    {
        signal(signal2child, childHandler);

        alarm(2);

        int iterNum = 10001;
        for (int i = 0; i < iterNum; i++)
        {
            printf("Child iteration number %d\n", i);
        }
    }
    else
    {
        signal(SIGCHLD, childReaper9);

        pause();
    }

    return 0;
}

void childReaper9(int signum) {
    int status;
    int cpid = wait(&status);
    printf("Child with PID %d has ended with status %d\n", cpid, status);
    printf("\n==== question 9 end ====\n");
    exit(0);
}