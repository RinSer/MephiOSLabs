#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
Повторить п. 2, создавая параллельные процессы с помощью связки fork - exec. 
Как передать дескрипторы канала в порожденный процесс?
*/

int q4()
{
    printf("=== question 4 start ===\n\n");

    char char_buff[1];
    int write_to_parent[2];

    if (pipe(write_to_parent) < 0)
        return catch();

    char* file_desc = malloc(255);
    sprintf(file_desc, "%d", write_to_parent[1]);

    int child_pid = fork();

    if (child_pid > 0)
    {
        close(write_to_parent[1]);

        while (read(write_to_parent[0], char_buff, sizeof(char_buff)) > 0)
            write(STDOUT_FILENO, char_buff, sizeof(char_buff));

        close(write_to_parent[0]);
    }
    else
    {
        close(write_to_parent[0]);
        execl("q4exec", "q4exec", file_desc);
    }

    free(file_desc);

    printf("\n==== question 4 end ====\n");

    return 0;
}

int q4exec(char* write_fd) 
{
    int fd = atoi(write_fd);
    
    char child_message[] = "This should be parent's output\n";

    write(fd, child_message, sizeof(child_message) - 1);

    close(fd);

    return 0;
}