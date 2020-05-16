#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
Модифицировать программу п. 1 таким образом, 
чтобы родительский процесс читал из канала в цикле, 
пока не встретится конец файла (порожденный процесс может записывать в канал информацию, 
читаемую им из стандартного входного потока). 
Как избежать бесконечного ожидания родительским процессом чтения из пустого канала?
*/

int q2()
{
    printf("=== question 2 start ===\n\n");

    char child_message[] = "This should be parent's output\n";
    char char_buff[1];
    int write_to_parent[2];

    if (pipe(write_to_parent) < 0)
        return catch ();

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

        write(write_to_parent[1], child_message, sizeof(child_message) - 1);

        close(write_to_parent[1]);

        exit(0);
    }

    printf("\n==== question 2 end ====\n");

    return 0;
}