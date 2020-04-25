#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Изменить программу п. 3 так, чтобы родительский процесс завершился раньше порожденного. 
Какой процесс становится родительским для порожденного после того, 
как исходный родительский процесс завершился?
*/

int q4()
{
    int pid = fork();

    if (pid < 0) return catch();

    if (pid == 0)
    {
        printPIDs("Child with parent");

        while (kill(getppid(), 0) >= 0) {
            printf("Waiting for parent to finish...>");
        }
        printf("\n");
    }
    
    printPIDs(pid > 0 ? "Parent" : "Orphaned");

    return 0;
}