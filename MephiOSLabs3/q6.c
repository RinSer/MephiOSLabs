#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Повторить выполнение п. 5 задания, изменив сигнал, 
посылаемый в порожденный процесс. Что изменится?
*/

void childReaper6(int);
void childHandler(int);

int q6()
{
    printf("=== question 6 start ===\n\n");

    int signal2child = SIGUSR2;

    int pid = fork();

    if (pid < 0) return catch ();

    if (pid == 0)
    {
        //signal(signal2child, childHandler);

        int iterNum = 1000001;
        for (int i = 0; i < iterNum; i++)
        {
            printf("Child iteration number %d\n", i);
        }
    }
    else
    {
        signal(SIGCHLD, childReaper6);

        kill(pid, signal2child);

        pause();
    }

    return 0;
}

void childReaper6(int signum) {
    int status;
    int cpid = wait(&status);
    printf("Child with PID %d has ended with status %d\n", cpid, status);
    printf("\n==== question 6 end ====\n");
    exit(0);
}