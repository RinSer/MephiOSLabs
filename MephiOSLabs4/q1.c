#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
Создать параллельный процесс, используя только fork. 
Организовать обмен информацией между процессами через каналы. 
Предусмотреть однонаправленную и двунаправленную связь. 
При создании двунаправленной связи исключить возможность появления «смертельных объятий».
*/

int q1()
{
    printf("=== question 1 start ===\n\n");
    
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
        close(write_to_parent[1]);
        close(write_to_child[0]);

        write(write_to_child[1], parent_message, sizeof(parent_message)-1);

        close(write_to_child[1]);

        while (read(write_to_parent[0], char_buff, sizeof(char_buff)) > 0)
            write(STDOUT_FILENO, char_buff, sizeof(char_buff));
        
        close(write_to_parent[0]);
    }
    else
    {
        close(write_to_child[1]);
        close(write_to_parent[0]);

        while (read(write_to_child[0], char_buff, sizeof(char_buff)) > 0)
            write(STDOUT_FILENO, char_buff, sizeof(char_buff));

        close(write_to_child[0]);

        write(write_to_parent[1], child_message, sizeof(child_message)-1);

        close(write_to_parent[1]);

        exit(0);
    }

    printf("\n==== question 1 end ====\n");

    return 0;
}