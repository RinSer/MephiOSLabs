#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/*
Написать программу, которая определяет, 
какой файл из перечисленных в командной строке имеет наибольшую длину. 
Вывести длину файла в байтах.
*/

int q11(int argc, char* argv[])
{
    printf("=== question 11 start ===\n\n");

    int max_size = -1;
    char max_file[255];
    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);
        catch();
        int file_length = lseek(fd, 0, SEEK_END);
        catch();

        if (file_length > max_size)
        {
            max_size = file_length;
            strcpy(max_file, argv[i]);
            catch();
        }
    }

    printf("maximum file length is %d\n", max_size);
    printf("longest file name is %s\n", max_file);

    printf("\n==== question 11 end ====\n");

    return 0;
}