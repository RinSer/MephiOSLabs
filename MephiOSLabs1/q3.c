#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*
Повторно выполнить программу п. 2 с теми же исходными данными; 
проверить результаты выполнения каждого системного вызова. 
Объяснить полученные результаты.
*/

int q3(char* arg)
{
    printf("=== question 3 start ===\n\n");

    if (arg == NULL || sizeof(arg) == 0) 
    {
        printf("please enter the name of file to create as cmd arg!");
        return -1;
    }

    if (access(arg, F_OK) != -1) remove(arg);
    else suppress();

    int bytes_size = 1;

    int fd = open(arg, O_CREAT | O_WRONLY);
    if (catch() < 0) return -1;
    printf("sys call result fd = %d\n", fd);

    char file_lines[] = "First line test input.\nSecond line test input.\nThird line test input.\n";

    printf("wrote %d bytes to file %s\n", write(fd, file_lines, sizeof(file_lines)), arg);
    if (catch() < 0) return -1;

    printf("sys call close result = %d\n", close(fd));
    if (catch() < 0) return -1;

    fd = open(arg, O_RDONLY);
    if (catch() < 0) return -1;
    printf("sys call result fd = %d\n", fd);

    char fc;
    int bytes_count = read(fd, &fc, bytes_size);
    while (fc != NULL)
    {
        putchar(fc);
        bytes_count += read(fd, &fc, bytes_size);
        if (catch() < 0) return -1;
    }
    printf("have read %d bytes from file %s\n", bytes_count, arg);

    printf("sys call close result = %d\n", close(fd));
    if (catch() < 0) return -1;

    fd = open(arg, O_RDWR);
    if (fd == -1)
        return catch();
    else
        printf("sys call result fd = %d\n", fd);

    printf("\n==== question 3 end ====\n");

    return 0;
}