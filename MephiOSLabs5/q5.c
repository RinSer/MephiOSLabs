#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
С помощью системных вызовов pipe и dup реализовать конвейер: who | wc -l.
*/

int q5()
{
    printf("=== question 5 start ===\n\n");

    int pipe_fds[2];

    pipe(pipe_fds);

    if (fork() == 0)
    {
        close(pipe_fds[0]);

        dup2(pipe_fds[1], STDOUT_FILENO);

        system("who");

        exit(0);
    }
    else
    {
        close(pipe_fds[1]);

        wait(NULL);

        dup2(pipe_fds[0], STDIN_FILENO);

        system("wc -l");
    }

    printf("\n==== question 5 end ====\n");

    return 0;
}
