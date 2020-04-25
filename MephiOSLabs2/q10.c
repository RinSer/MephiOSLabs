#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
������� (� ������� ������ fork - exec) ������������ �������. 
��� ������������ ����� ��� exec ���������� � ������� ��������� ��������� ������. 
�������� � ����������� ������� ��������� ���������� ����� ������ ���������� (������ ���������� � ������� main). 
������ ������� (� ������������, � �����������) ������ ������� �� ����� ������ ���������� ��� ���������� � ���� ���������.
*/

extern char** environ;
int q10(int argc, char* argv[])
{
    int pid = fork();

    if (pid < 0) return catch();

    if (pid > 0)
    {
        int status;
        wait(&status);
        
        printf("Current process name: %s\n", argv[0]);
        printArgs(argc, argv);
        printCurrentEnvironment(environ);
        printf("\n");
    }
    else 
        execv(argv[1], argv + 1);

    return 0;
}