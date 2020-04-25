#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/*
Изменить программу п. 8 таким образом, чтобы функция копирования использовала стандартные ввод и вывод, 
а вызывающая программа переназначала стандартные ввод и вывод на указанные в аргументах командной строки файлы.
*/

int q9(char* arg1, char* arg2)
{
    printf("=== question 9 start ===\n\n");

    char file_name1[255], file_name2[255];
    char terminal[] = "/dev/tty";

    if (arg1 == NULL || sizeof(arg1) == 0)
    {
        printf("Enter source file name:\n");
        scanf("%255s", &file_name1);
    }
    else
        strcpy(file_name1, arg1);

    if (arg2 == NULL || sizeof(arg1) == 0)
    {
        printf("Enter destination file name:\n");
        scanf("%255s", &file_name2);
    }
    else
        strcpy(file_name2, arg2);

    stdin = open(file_name1, O_RDONLY);
    if (catch() < 0) return -1;

    if (access(file_name2, F_OK) != -1) remove(file_name2);
    else suppress();

    stdout = open(file_name2, O_CREAT | O_WRONLY);
    if (catch() < 0) return -1;

    copy_std_stream();

    close(stdin);
    close(stdout);

    stdout = open(terminal, O_WRONLY);
    if (catch() < 0) return -1;
    char copy_message[255];
    sprintf(copy_message, "%s file has been copied from %s\n", file_name2, file_name1);
    write(stdout, copy_message, strlen(copy_message));
    char final_message[] = "\n==== question 9 end ====\n";
    write(stdout, final_message, strlen(final_message));
    close(stdout);

    return 0;
}

int copy_std_stream()
{
    int src_size = lseek(stdin, 0, SEEK_END);
    if (catch() < 0) return -1;

    lseek(stdin, 0, SEEK_SET);
    if (catch() < 0) return -1;

    char buffer[src_size];
    read(stdin, buffer, src_size);
    if (catch() < 0) return -1;
    
    write(stdout, buffer, src_size);
    if (catch() < 0) return -1;

    return 0;
}