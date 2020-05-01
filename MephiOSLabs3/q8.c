#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
Открыть файл (достаточно большого размера), доступный для чтения. Имя файла передается из командной строки. 
После открытия файла создать параллельный процесс с помощью только fork. 
В обоих процессах создать свои файлы для записи, 
читать информацию из общего файла и копировать ее в собственные выходные файлы (не на экран). 
Вывести на экран содержимое полученных файлов из порожденного процесса по окончании записи в файл и из родительского процесса, 
дождавшись завершения порожденного процесса. 
Посмотреть, что изменится, если читаемую процессами информацию сразу выводить на экран.
*/

char ParentFileName[] = "parentCopy8";
char ChildFileName[] = "childCopy8";

void onSighup()
{
    signal(SIGHUP, onSighup); /* reset signal */

    int pfd = open(ParentFileName, O_RDONLY);
    catch();
    int cfd = open(ChildFileName, O_RDONLY);
    catch();

    printf("Child prints parent file\n");
    copyFileTo("", pfd, 1);
    close(pfd);

    printf("\nChild prints child file\n");
    copyFileTo("", cfd, 1);
    close(cfd);

    exit(0);
}

int q8()
{
    int fd = open("/home/rinser/test8", O_RDONLY);

    int pid = fork();

    if (pid < 0) return catch();

    if (pid > 0)
    {
        copyFileTo(ParentFileName, fd, -1);

        kill(pid, SIGHUP);

        int status;
        wait(&status);
    }
    else
    {
        copyFileTo(ChildFileName, fd, -1);
        
        signal(SIGHUP, onSighup);
        for (;;);
    }

    close(fd);

    return 0;
}

int copyFileTo(char fileName[], int cpd, int fd) 
{
    if (fd < 0)
    {
        if (access(fileName, F_OK) != -1) remove(fileName);
        else suppress();
        
        fd = open(fileName, O_RDWR | O_CREAT);
        catch ();
    }

    int file_size = lseek(cpd, 0, SEEK_END);
    lseek(cpd, 0, SEEK_SET);

    char buffer[file_size];

    read(cpd, buffer, file_size);

    write(fd, buffer, file_size);

    if (fd > 1) close(fd);
    close(cpd);

    return 0;
}