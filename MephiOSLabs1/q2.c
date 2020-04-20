#include <stdio.h>
#include <fcntl.h>

/*
������� ����� ���� � ������ ������ �� ������ (��� ����� � ����� ������� ������ �� ��������� ������), 
�������� � ���� ��������� �����, �������. �������� ������� ������ ���� �� ������, 
��������� �� ���� ���������� � ������� �� �� �����, �������. 
��� ��� ������� ���� �� ���� �� ������ � ������, ��������� ��������� ���������� ������ open. 
��������� ���������� ����������.
*/

int q2()
{
    printf("=== question 2 start ===\n\n");

    int bytes_size = 1;
    char file_name[255], file_perms[2];

    // ��� ����� � ����� ������� ������ �� ��������� ������
    printf("Enter file name:\n");
    scanf("%255s", &file_name);
    printf("Enter file rights:\n");
    scanf("%1s", &file_perms); // w

    // ������� ����� ���� � ������ ������ �� ������
    FILE* fp = fopen(&file_name, file_perms);
    if (catch () < 0) return -1;

    // �������� � ���� ��������� �����
    char file_lines[] = "First line test input.\nSecond line test input.\nThird line test input.\n";

    fwrite(file_lines, bytes_size, sizeof(file_lines), fp);
    if (catch() < 0) return -1;

    // �������
    fclose(fp);
    if (catch() < 0) return -1;

    // �������� ������� ������ ���� �� ������
    fp = fopen(&file_name, "r");
    if (catch() < 0) return -1;

    // ��������� �� ���� ���������� � ������� �� �� �����
    char fc;
    while ((fc = fgetc(fp)) != NULL)
        putchar(fc);
    if (catch() < 0) return -1;

    // �������
    fclose(fp);
    if (catch() < 0) return -1;

    // ��� ��� ������� ���� �� ���� �� ������ � ������, 
    // ��������� ��������� ���������� ������ open
    int fd = open(file_name, O_RDWR);
    if (fd == -1)
        return catch();
    else
        printf("sys call result fd = %d\n", fd);

    printf("\n==== question 2 end ====\n");

    return 0;
}