#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
�������� ��������� �. 3 ���, ����� ������������ ������� ���������� ������ ������������. 
����� ������� ���������� ������������ ��� ������������ ����� ����, 
��� �������� ������������ ������� ����������?
*/

int q4()
{
    int pid = fork();

    if (pid < 0) return catch();

    if (pid == 0)
    {
        printPIDs("Child with parent");

        while (kill(getppid(), 0) >= 0) {
            printf("Waiting for parent to finish...>");
        }
        printf("\n");
    }
    
    printPIDs(pid > 0 ? "Parent" : "Orphaned");

    return 0;
}