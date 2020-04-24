#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

/*
Написать программу для получения справочной информации о файлах с помощью системного вызова stat. 
Имя файла передается в программу из командной строки. 
Получить справочную информацию для различных типов файлов 
(обычный файл, каталог, специальные байт- и блок-ориентированные файлы).
*/

int q7(char* arg)
{
    printf("=== question 7 start ===\n\n");

    char file_name[255];
    struct stat file_stat;

    if (arg == NULL || sizeof(arg) == 0)
    {
        // имя файла ввести из командной строки
        printf("Enter file name:\n");
        scanf("%255s", &file_name);
    }
    else
        strcpy(file_name, arg);

    if (stat(&file_name, &file_stat) != 0) return catch();

    // определить тип файла
    if (S_ISREG(file_stat.st_mode)) 
        printf("%s is a regular file\n", file_name);
    if (S_ISDIR(file_stat.st_mode)) 
        printf("%s is a directory\n", file_name);
    if (S_ISCHR(file_stat.st_mode)) 
        printf("%s is a character device\n", file_name);
    if (S_ISBLK(file_stat.st_mode)) 
        printf("%s is a block device\n", file_name);
    if (S_ISLNK(file_stat.st_mode)) 
        printf("%s is a symbolic link\n", file_name);

    printf("%s file size is %d bytes\n", file_name, file_stat.st_size);
    printf("%s file last access time is %s\n", file_name, ctime(&file_stat.st_atime));
    printf("%s file last modification time is %s\n", file_name, ctime(&file_stat.st_mtime));
    printf("%s file last status change time is %s\n", file_name, ctime(&file_stat.st_ctime));

    printf("==== question 7 end ====\n");

    return 0;
}