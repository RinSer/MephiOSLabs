#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Создать два параллельных процесса, 
разделяющие ввод с клавиатуры и вывод на экран. 
Что получится при исполнении этих процессов?
*/

int q10()
{
    char buff[1];

    int child_pid = fork();
    if (child_pid < 0)
        return catch();

    if (child_pid > 0)
    {
        for (;;)
        {
            read(STDIN_FILENO, buff, sizeof(buff));
            printf("Parent output:\n");
            write(STDOUT_FILENO, buff, sizeof(buff));
        }
    }
    else
    {
        for (;;)
        {
            read(STDIN_FILENO, buff, sizeof(buff));
            printf("Child output:\n");
            write(STDOUT_FILENO, buff, sizeof(buff));
        }
    }

    return 0;
}