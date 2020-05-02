#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Повторить выполнение предыдущих пунктов задания, 
используя в порожденном процессе вместо вложенных циклов системный вызов pause. 
Что изменится? Как завершить процесс в случае выполнения с pause п. 4?
*/

void childReaper7(int);
void childHandler(int);

int q7()
{
    printf("=== question 7 start ===\n\n");

    int signal2child = SIGUSR1;

    int pid = fork();

    if (pid < 0) return catch();

    if (pid == 0)
    {
        //signal(signal2child, childHandler);
        
        pause();
    }
    else
    {
        signal(SIGCHLD, childReaper7);

        //kill(pid, signal2child);

        pause();
    }

    return 0;
}

void childReaper7(int signum) {
    int status;
    int cpid = wait(&status);
    printf("Child with PID %d has ended with status %d\n", cpid, status);
    printf("\n==== question 7 end ====\n");
    exit(0);
}