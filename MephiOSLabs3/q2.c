#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
Кто выполняется первым после fork: отец или сын? 
Написать программу, которую можно использовать для проверки данной ситуации.
*/

int q2()
{
    int pid = fork();

    if (pid < 0) return catch();

    if (pid == 0)
        printf("This is child process output\n");
    else
        printf("This is parent process output\n");

    return 0;
}