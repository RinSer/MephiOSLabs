#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Написать программу, исключающую появление зомби для завершающихся порожденных процессов.
*/

void childReaper(int);

int q3()
{
    printf("=== question 3 start ===\n\n");

    signal(SIGCHLD, childReaper);

    int pid = fork();

    if (pid < 0) return catch();

    if (pid > 0)
    {
        printf("%d's parent went to sleep\n", pid);
        pause();
    }
    else
    {
        printf("PID %d wants to become Zombie\n", getpid());
        exit(0);
    }

    return 0;
}

void childReaper(int signum) {
    int status;
    int cpid = wait(&status);
    printf("Child with PID %d has ended with status %d\n", cpid, status);
    sleep(5);
    printf("\n==== question 3 end ====\n");
    exit(0);
}