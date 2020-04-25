#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
Выполнить п. 8 при условии, что общий файл для чтения открывается в каждом из порожденных процессов.
*/

char ParentFileName9[] = "parentCopy9";
char ChildFileName9[] = "childCopy9";

void onSighup2()
{
    signal(SIGHUP, onSighup2); /* reset signal */

    int pfd = open(ParentFileName9, O_RDONLY);
    catch();
    int cfd = open(ChildFileName9, O_RDONLY);
    catch();

    printf("Child prints parent file\n");
    copyFileTo("", pfd, 1);
    close(pfd);

    printf("\nChild prints child file\n");
    copyFileTo("", cfd, 1);
    close(cfd);

    exit(0);
}

int q9()
{
    int fd;
    
    int pid = fork();

    if (pid < 0) return catch();

    if (pid > 0)
    {
        fd = open("/home/rinser/test8", O_RDONLY);
        
        copyFileTo(ParentFileName9, fd, -1);

        kill(pid, SIGHUP);

        int status;
        wait(&status);
    }
    else
    {
        fd = open("/home/rinser/test8", O_RDONLY);
        
        copyFileTo(ChildFileName9, fd, -1);

        signal(SIGHUP, onSighup2);
        for (;;);
    }

    close(fd);

    return 0;
}