#include <stdio.h>
#include <errno.h>

/*
������� ��� ����� ������
*/

extern int errno;
int catch()
{
    if (errno > 0)
    {
        perror("Error");
        return -1;
    }
    return 0;
}

void suppress() 
{
    errno = 0;
}