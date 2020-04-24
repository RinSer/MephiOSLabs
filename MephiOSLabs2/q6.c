#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
Модифицировать программу п. 4 для создания разреженного файла.
*/

int q6(char* arg)
{
    printf("=== question 6 start ===\n\n");

    if (arg == NULL || sizeof(arg) == 0)
    {
        printf("please enter the name of file to create as cmd arg!");
        return -1;
    }

    // удалить файл, если он существует
    if (access(arg, F_OK) != -1) remove(arg);
    else suppress();

    int bytes_size = 1;

    int fd = open(arg, O_RDWR | O_CREAT);
    if (catch() < 0) return -1;

    // записать в него строкy
    char first_line[] = "First line test input.\n";
    add_line(fd, first_line, bytes_size);

    // добавляем разреженность (дырку)
    int hole_size = 1000;
    lseek(fd, hole_size, SEEK_CUR);

    // и ещё строку
    add_line(fd, "Second line test input.\n", bytes_size);

    // прочитать содержимое файла
    char fc;
    printf("current offset from file start is %d\n", lseek(fd, 0, SEEK_SET));
    while (read(fd, &fc, bytes_size) > 0)
        putchar(fc);

    lseek(fd, hole_size + strlen(first_line), SEEK_SET);
    while (read(fd, &fc, bytes_size) > 0)
        putchar(fc);

    printf("current offset from file start is %d\n", lseek(fd, 0, SEEK_CUR));

    // закрыть
    close(fd);
    if (catch() < 0) return -1;

    printf("\n==== question 6 end ====\n");

    return 0;
}

int add_line(int fd, char* file_lines, int bytes_size)
{
    int len = strlen(file_lines);
    int bytes_count = 0;
    for (int i = 0; i < len; i++)
    {
        bytes_count += write(fd, &file_lines[i], bytes_size);
        if (catch() < 0) return -1;
    }
}