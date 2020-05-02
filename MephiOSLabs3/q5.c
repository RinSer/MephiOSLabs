#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/*
Из родительского процесса послать в порожденный процесс сигнал (SIGUSR1). 
Посмотреть, какой статус будет передан в родительский процесс в этом случае. 
Сколько итераций выполнится в порожденном процессе?
*/

void childReaper5(int);
void childHandler(int);

int q5()
{
    printf("=== question 5 start ===\n\n");

    int signal2child = SIGUSR1;

    int pid = fork();

    if (pid < 0) return catch();

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
        signal(SIGCHLD, childReaper5);

        //sleep(1);

        kill(pid, signal2child);

        pause();
    }

    return 0;
}

void childReaper5(int signum) {
    int status;
    int cpid = wait(&status);
    //printf("stderr output:\n");
    //printStderr();
    printf("Child with PID %d has ended with status %d\n", cpid, status);
    printf("\n==== question 5 end ====\n");
    exit(0);
}

void childHandler(int signum) {
    printf("Child caught signal %d\n", signum);
    exit(0);
}

void printStderr() {
    int ed = open(stderr, O_RDONLY);
    int size = lseek(ed, 0, SEEK_END);
    lseek(ed, 0, SEEK_SET);
    char buffer[size];
    write(ed, buffer, size);
    printf("%s\n", buffer);
}