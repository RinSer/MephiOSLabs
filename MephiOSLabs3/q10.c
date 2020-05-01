#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Создать (с помощью связки fork - exec) параллельный процесс. 
Имя исполняемого файла для exec передается с помощью аргумента командной строки. 
Передать в порожденный процесс некоторую информацию через список параметров (список аргументов в функции main). 
Каждый процесс (и родительский, и порожденный) должен вывести на экран список переданных ему аргументов и свое окружение.
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

int printCurrentEnvironment(char* env[])
{
    for (char** v = env; *v != 0; v++)
        printf("%s\n", *v);

    return catch ();
}

printArgs(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
        printf("Arg %d value = %s\n", i, argv[i]);
}