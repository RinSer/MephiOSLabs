#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
�������������� ���������, ������� � ��� setpgrp � ����������� ������� �� ����, ��� �� ����� ��������� pause. 
�������� �� �� ����������� ������� ������� ������� ���������� � ��� ������, ����� ������������ ������� "����"? 
����� �� ������� ����������� ������� � ������ ������� ps?
*/

int q7()
{
    int pid = fork();

    if (pid < 0) return catch();

    if (pid > 0)
    {
        printPIDs("Parent");

        pause();

        int status;
        if (waitpid(pid, &status, 0) == pid)
        {
            printf("\nChild process PID was %d\n", pid);
            printf("Child process exited with %d status\n\n", status);
        }
        else
            return catch();
    }
    else
    {
        char processName[] = "Child";
        
        printPIDs(processName);

        printf("%s process new GRPPID=%d\n", processName, setpgrp());

        pause();
    }

    return 0;
}