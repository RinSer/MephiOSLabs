#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
�������� ���������, � ������� ������� ��������� ����� � ��������� ������������ �������� �����������. 
��� �������� ������ �������� ���� �������������� (��������, ������������� ��������, ������ ���������). 
��������� ������������� � ������ ���������� ������������ ��������. 
��������� ������ ��������� � ���������� �� ����������.
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