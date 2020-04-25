#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Написать программу, в которой процесс порождает новый и позволяет порожденному процессу завершиться. 
Оба процесса должны выводить свои идентификаторы (процесса, родительского процесса, группы процессов). 
Проверить идентификатор и статус завершения порожденного процесса. 
Выполнить данную программу и посмотреть ее результаты.
*/

int q3()
{
    int pid = fork();

    if (pid < 0) return catch();

    if (pid > 0)
    {
        int status;
        if (waitpid(pid, &status, 0) == pid)
        {
            printf("\nChild process PID was %d\n", pid);
            printf("Child process exited with %d status\n\n", status);
        }
        else
            return catch();
    }
    
    printPIDs("This");

    return 0;
}

int printPIDs(char processName[]) {

    printf("%s process PID=%d\n", processName, getpid());
    printf("%s process PPID=%d\n", processName, getppid());
    printf("%s process GRPPID=%d\n", processName, getpgrp());

    return 0;
}