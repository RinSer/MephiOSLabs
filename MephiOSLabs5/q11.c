#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Повторить выполнение п. 10, 
включив в процессы для синхронизации работы с терминалом использование режима слабой блокировки. 
Как изменится поведение процессов?
*/

int q11()
{
    char buff[1];

    int child_pid = fork();
    if (child_pid < 0)
        return catch();

    if (child_pid > 0)
    {
        struct flock lock;
        
        /*lock.l_start = 0;
        lock.l_whence = SEEK_CUR;
        lock.l_len = 0;
        lock.l_pid = getpid();
        lock.l_type = F_RDLCK;*/

        if (fcntl(STDIN_FILENO, F_GETLK, &lock) < 0)
            return catch();
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
