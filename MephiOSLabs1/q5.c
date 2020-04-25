#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*
Повторно выполнить программу п. 4; 
проверить результаты выполнения каждого системного вызова. 
Объяснить полученные результаты.
*/

int q5(char* arg)
{
    printf("=== question 5 start ===\n\n");

    if (arg == NULL || sizeof(arg) == 0)
    {
        printf("please enter the name of file to create as cmd arg!");
        return -1;
    }

    if (access(arg, F_OK) != -1) remove(arg);
    else suppress();

    int bytes_size = 1;

    int fd = open(arg, O_RDWR | O_CREAT);
    if (catch() < 0) return -1;
    printf("sys call result fd = %d\n", fd);

    char file_lines[] = "First line test input.\nSecond line test input.\nThird line test input.\n";
    int len = sizeof(file_lines);
    int bytes_count = 0;
    for (int i = 0; i < len; i++)
    {
        printf("current offset from file start is %d\n", lseek(fd, i, SEEK_SET));
        bytes_count += write(fd, &file_lines[i], bytes_size);
        if (catch() < 0) return -1;
    }
    printf("have read %d bytes from file %s\n", bytes_count, arg);

    char fc;
    printf("current offset from file start is %d\n", lseek(fd, 0, SEEK_SET));
    while (read(fd, &fc, bytes_size) > 0)
        putchar(fc);

    printf("current offset from file start is %d\n", lseek(fd, 0, SEEK_CUR));

    close(fd);
    if (catch() < 0) return -1;

    printf("\n==== question 5 end ====\n");

    return 0;
}