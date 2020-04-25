#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Изменить программу п. 3 так, чтобы родительский процесс выполнялся, 
не ожидая завершения порожденного процесса. 
Что произойдет с порожденным процессом, когда он завершится? Как убить зомби?
*/

int q5()
{
    int pid = fork();

    if (pid < 0) return catch ();

    if (pid > 0)
    {
        printf("%d's parent went to sleep\n", pid);
        sleep(50);
        printPIDs("Awaken parent of zombie");
    }
    else
    {
        printPIDs("Zombie");
        exit(0);
    }

    return 0;
}