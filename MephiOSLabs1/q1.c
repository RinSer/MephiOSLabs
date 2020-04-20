#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

/*
�������� ���������, ������� ��������� ��������� ��������� �����, �������� open, � ����� ������� ������������ ������. 
������������ � ��������� ������ ������� ������ ��������� �� ������: 
����� �������� errno, 
����� ���������������� ��������� �� ���������� ������� ��������� �� ������� sys_errlist[], 
����� ������������ ������� perror.
*/

extern int errno;
extern const char* sys_errlist[];
int q1()
{
    printf("=== question 1 start ===\n\n");
    
    // ��������� ��������� ����� �� ������ �����
    int fd = open("unexisting.txt", O_RDONLY);

    if (fd == -1)
    {
        // ����� �������� errno (ENOENT)
        printf("error number: %d\n", errno);
        //printf("error number: %d\n", ENOENT);
        // ����� ��������� �� ���������� �������
        printf("sys_errlist[errno] = %s\n", sys_errlist[errno]);
        //printf("sys_errlist[errno] = %s\n", sys_errlist[ENOENT]);
        // ����� ������� perror
        perror("perror output");
    }

    printf("\n==== question 1 end ====\n");

    return 0;
}