#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Модифицировать программу, включив в нее setpgrp в порожденный процесс до того, как он будет выполнять pause. 
Повлияет ли на порожденный процесс нажатие клавиши прерывания в тот момент, когда родительский процесс "спит"? 
Будет ли показан порожденный процесс в выводе команды ps?
*/

int q7()
{
    int pid = fork();

    if (pid < 0) return catch();

    if (pid > 0)
    {
        printPIDs("Parent");

        pause();

        int status;
        if (waitpid(pid, &status, 0) == pid)
        {
            printf("\nChild process PID was %d\n", pid);
            printf("Child process exited with %d status\n\n", status);
        }
        else
            return catch();
    }
    else
    {
        char processName[] = "Child";
        
        printPIDs(processName);

        printf("%s process new GRPPID=%d\n", processName, setpgrp());

        pause();
    }

    return 0;
}