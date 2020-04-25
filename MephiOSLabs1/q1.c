#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

/*
Написать программу, которая выполняет некоторый системный вызов, например open, и затем выводит возвращаемую ошибку. 
Использовать в программе разные способы вывода сообщения об ошибке: 
вывод значения errno, 
вывод соответствующего сообщения из системного массива сообщений об ошибках sys_errlist[], 
вызов библиотечной функции perror.
*/

extern int errno;
extern const char* sys_errlist[];
int q1()
{
    printf("=== question 1 start ===\n\n");
    
    int fd = open("unexisting.txt", O_RDONLY);

    if (fd == -1)
    {
        printf("error number: %d\n", errno);
        //printf("error number: %d\n", ENOENT);
        
        printf("sys_errlist[errno] = %s\n", sys_errlist[errno]);
        //printf("sys_errlist[errno] = %s\n", sys_errlist[ENOENT]);
        
        perror("perror output");
    }

    printf("\n==== question 1 end ====\n");

    return 0;
}