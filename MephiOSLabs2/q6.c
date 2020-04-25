#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
�������� ��������� �. 3 ���, ����� ��� �������� ��������� ��������� ����� pause ����� ������ ���������������. 
��������� ��������� � ������� ������ � ���������� (� ������� ps), ����� �������� ���������� ��� ������� ������������. 
��������� kill -9 pid ��� ������������� ��������. ��� ���������� � �����������? 
����� ������� �������� ������, ����� ��������� ���������, �� ��� � ������������� ������. 
������ �� ��������� ������� CTRL-C. ��� ���������� � ������������ � ����������� ����������? 
����� �� �������� ����� �� ���������, ���� ������ ������� ���������� ����� ����, ��� ������������ ������� ����������?
*/

int q6()
{
    int pid = fork();

    if (pid < 0) return catch ();

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
            return catch ();
    }
    else
    {
        printPIDs("Child");

        pause();
    }

    return 0;
}