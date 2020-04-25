#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
Написать программу, которая выводит на экран содержимое файла в обратном порядке: 
сначала выводится последний символ файла, затем предпоследний и так далее до первого. 
Использовать lseek и read.
*/

int q10(char* arg)
{
    printf("=== question 10 start ===\n\n");

    char file_name[255];

    if (arg == NULL || sizeof(arg) == 0)
    {
        printf("Enter source file name:\n");
        scanf("%255s", &file_name);
    }
    else
        strcpy(file_name, arg);

    int bytes_size = 1;

    int fd = open(&file_name, O_RDONLY);
    if (catch() < 0) return -1;

    int file_size = lseek(fd, 0, SEEK_END);
    if (catch() < 0) return -1;

    lseek(fd, 0, SEEK_SET);
    if (catch() < 0) return -1;

    char fc;
    while (file_size > 0)
    {
        lseek(fd, --file_size, SEEK_SET);
        if (catch() < 0) return -1;

        read(fd, &fc, bytes_size);
        if (catch() < 0) return -1;

        putchar(fc);
    }

    close(fd);
    if (catch() < 0) return -1;

    printf("\n\n==== question 10 end ====\n");

    return 0;
}