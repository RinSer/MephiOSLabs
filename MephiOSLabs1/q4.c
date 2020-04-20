#include <stdio.h>
#include <fcntl.h>

/*
»спользу€ программу п. 2, создать новый файл с правами на чтение и запись; 
выполнить любые операции с файлом (чтение и/или запись), 
использу€ разные способы позиционировани€. 
ќбъ€снить полученные результаты.
*/

int q4()
{
    printf("=== question 4 start ===\n\n");

    int bytes_size = 1;
    char file_name[255];

    // им€ файла ввести из командной строки
    printf("Enter file name:\n");
    scanf("%255s", &file_name);

    // создать новый файл с правом на запись
    FILE* fp = fopen(&file_name, "w");
    if (catch() < 0) return -1;

    // записать в него несколько строк
    char file_lines[] = "First line test input.\nSecond line test input.\nThird line test input.\n";
    int len = sizeof(file_lines);
    for (int i = 0; i < len; i++)
    {
        if (fseek(fp, 0, SEEK_END) != 0) return catch();
        fputc(file_lines[i], fp);
    }
    int file_len = ftell(fp);
    // закрыть
    fclose(fp);
    if (catch() < 0) return -1;

    // прочитать содержимое файла
    fp = fopen(&file_name, "r");
    int i = 0;
    while (i < file_len)
    {
        if (fseek(fp, i++, SEEK_SET) != 0) return catch();
        putchar(fgetc(fp));
    }
    // закрыть
    fclose(fp);
    if (catch() < 0) return -1;

    printf("\n==== question 4 end ====\n");

    return 0;
}