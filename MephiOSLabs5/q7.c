#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
Создать два параллельных процесса, 
в каждом из которых осуществляется работа с одним и тем же файлом. 
Каждый процесс открывает файл (имя файла передается через список аргументов командной строки). 
Один процесс пишет в файл, другой - читает из него. Что произойдет без включения блокировок?
*/

int q7(char* file_path)
{
    printf("=== question 7 start ===\n\n");

    int fd;
    char buff[1];
    int child_pid = fork();

    if (child_pid < 0)
        return catch();

    if (child_pid > 0)
    {
        fd = open(file_path, O_RDONLY);
        if (fd < 0)
            return catch();

        while (read(fd, buff, sizeof(buff)) > 0)
            write(STDOUT_FILENO, buff, sizeof(buff));

        close(fd);
    }
    else
    {
        fd = open(file_path, O_WRONLY);
        if (fd < 0)
            return catch();

        char test_line[] = "Write something to the file\n";

        write(fd, test_line, sizeof(test_line) - 1);

        close(fd);

        exit(0);
    }
    
    printf("\n==== question 7 end ====\n");

    return 0;
}
