#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/*
Выполнить из программы на Си какую-либо команду Shell (cp или ls): 
с помощью вызовов fork-exec, с помощью библиотечной функции system. 
Необходимые для команды данные передать через аргументы командной строки.
*/

int q11(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Please enter cmd name and options separated by space\n");
        return -1;
    }

    // склеиваем массив аргументов в одну строку
    argv += 1;
    argc -= 1;
    int aggregateLength = argc;
    for (int i = 0; i < argc; i++)
        aggregateLength += strlen(argv[i]);

    char command[aggregateLength];

    for (int i = 0; i < argc; i++)
    {
        strcat(command, argv[i]);
        if (i != argc + 1)
            strcat(command, " ");
    }

    int pid = fork();

    if (pid > 0)
    {
        int status;
        wait(&status);

        printf("\nParent process executes command using system() function:\n");

        system(command);
    }
    else
    {
        printf("Child process executes command using execv() function:\n");

        char* cmd[] = { "sh", "-c", command, NULL };

        execvp("/usr/bin/sh", cmd);
    }

    return 0;
}
