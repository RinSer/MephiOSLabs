#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Изменить программу п. 3 так, чтобы оба процесса выполняли системный вызов pause после вывода идентификаторов. 
Запустить программу в фоновом режиме и посмотрите (с помощью ps), какие процессы существуют для данного пользователя. 
Выполнить kill -9 pid для родительского процесса. Что произойдет с порожденным? 
После очистки текущего сеанса, вновь выполнить программу, но уже в интерактивном режиме. 
Нажать на терминале клавишу CTRL-C. Что произойдет с родительским и порожденным процессами? 
Можно ли получить такой же результат, если нажать клавишу прерывания после того, как родительский процесс завершится?
*/

int q6()
{
    int pid = fork();

    if (pid < 0) return catch ();

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
            return catch ();
    }
    else
    {
        printPIDs("Child");

        pause();
    }

    return 0;
}