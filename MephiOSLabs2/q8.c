#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/*
Написать программу копирования одного файла в другой. 
Имена файлов задаются в командной строке (первый аргумент - исходный файл, второй - результирующий). 
Если аргументы командной строки отсутствуют, использовать стандартный ввод и стандартный вывод. 
Копирование файлов выполнить с помощью функции.
*/

int q8(char* arg1, char* arg2)
{
    printf("=== question 8 start ===\n\n");

    char file_name1[255], file_name2[255];

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

    copy_file(file_name1, file_name2);

    printf("\n==== question 8 end ====\n");

    return 0;
}

int copy_file(char* src, char* dst)
{
    int srcd = open(src, O_RDONLY);
    if (catch() < 0) return -1;

    // удалить файл, если он существует
    if (access(dst, F_OK) != -1) remove(dst);
    else suppress();
    
    int dstd = open(dst, O_CREAT | O_WRONLY);
    if (catch() < 0) return -1;

    int src_size = lseek(srcd, 0, SEEK_END);
    if (catch() < 0) return -1;

    lseek(srcd, 0, SEEK_SET);
    if (catch() < 0) return -1;

    // копируем содержимое первого файла в память
    char buffer[src_size];
    read(srcd, buffer, src_size);
    if (catch() < 0) return -1;
    // записываем во второй файл
    write(dstd, buffer, src_size);
    if (catch() < 0) return -1;

    close(srcd);
    close(dstd);

    printf("%s file has been copied from %s\n", dst, src);

    return 0;
}