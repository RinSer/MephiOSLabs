#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
�������� ��������� �. 3 ���, ����� ������������ ������� ����������, 
�� ������ ���������� ������������ ��������. 
��� ���������� � ����������� ���������, ����� �� ����������? ��� ����� �����?
*/

int q5()
{
    int pid = fork();

    if (pid < 0) return catch ();

    if (pid > 0)
    {
        printf("%d's parent went to sleep\n", pid);
        sleep(50);
        printPIDs("Awaken parent of zombie");
    }
    else
    {
        printPIDs("Zombie");
        exit(0);
    }

    return 0;
}