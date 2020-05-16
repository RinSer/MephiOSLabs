#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
Модифицировать программу п. 2 таким образом, 
чтобы процессы реализовали двунаправленную связь (диалог).
*/

int q3()
{
    printf("=== question 3 start ===\n\n");

    char child_message[] = "This should be parent's output\n";
    char parent_message[] = "This should be child's output\n";
    char char_buff[1];
    int write_to_child[2], write_to_parent[2];

    if (pipe(write_to_child) < 0)
        return catch();
    if (pipe(write_to_parent) < 0)
        return catch();

    int child_pid = fork();

    if (child_pid > 0)
    {
        close(write_to_child[0]);

        int i = 0;
        write(write_to_child[1], &parent_message[i], sizeof(char_buff));
        while (read(write_to_parent[0], char_buff, sizeof(char_buff)) > 0)
        {
            write(STDOUT_FILENO, char_buff, sizeof(char_buff));
            if (i < sizeof(parent_message) - 1)
                write(write_to_child[1], &parent_message[++i], sizeof(char_buff));
            if (i == sizeof(parent_message) - 1)
            {
                close(write_to_child[1]);
                close(write_to_parent[1]);
            }
        }
        close(write_to_parent[0]);
    }
    else
    {
        close(write_to_parent[0]);

        int i = 0;
        write(write_to_parent[1], &child_message[i], sizeof(char_buff));
        while (read(write_to_child[0], char_buff, sizeof(char_buff)) > 0)
        {
            write(STDOUT_FILENO, char_buff, sizeof(char_buff));
            if (i < sizeof(child_message) - 1)
                write(write_to_parent[1], &child_message[++i], sizeof(char_buff));
            if (i == sizeof(child_message) - 1)
            {
                close(write_to_parent[1]);
                close(write_to_child[1]);
            }
        }
        close(write_to_child[0]);
        exit(0);
    }

    printf("\n==== question 3 end ====\n");

    return 0;
}