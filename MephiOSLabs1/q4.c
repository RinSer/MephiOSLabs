#include <stdio.h>
#include <fcntl.h>

/*
Используя программу п. 2, создать новый файл с правами на чтение и запись; 
выполнить любые операции с файлом (чтение и/или запись), 
используя разные способы позиционирования. 
Объяснить полученные результаты.
*/

int q4()
{
    printf("=== question 4 start ===\n\n");

    int bytes_size = 1;
    char file_name[255];

    printf("Enter file name:\n");
    scanf("%255s", &file_name);

    FILE* fp = fopen(&file_name, "w");
    if (catch() < 0) return -1;

    char file_lines[] = "First line test input.\nSecond line test input.\nThird line test input.\n";
    int len = sizeof(file_lines);
    for (int i = 0; i < len; i++)
    {
        if (fseek(fp, 0, SEEK_END) != 0) return catch();
        fputc(file_lines[i], fp);
    }
    int file_len = ftell(fp);
    
    fclose(fp);
    if (catch() < 0) return -1;

    fp = fopen(&file_name, "r");
    int i = 0;
    while (i < file_len)
    {
        if (fseek(fp, i++, SEEK_SET) != 0) return catch();
        putchar(fgetc(fp));
    }
    
    fclose(fp);
    if (catch() < 0) return -1;

    printf("\n==== question 4 end ====\n");

    return 0;
}