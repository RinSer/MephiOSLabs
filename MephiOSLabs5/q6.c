#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Создать именованный канал (любым способом). 
Убедиться, что канал создан. 
Рассмотреть особенности работы с именованным каналом 
(открыть файл с установленным и не установленным флагом O_NDELAY). 
Использовать его для обмена информацией с процессом, 
созданным другим пользователем (своим соседом).
*/

#define PIPE_PATH "/tmp/pipe6"
#define NEXT_LINE '\n'

int q6()
{
    printf("=== question 6 start ===\n\n");

    char* message = NULL;
    size_t message_size;

    if (mkfifo(PIPE_PATH, 0666) < 0)
        return catch();

    int pipe_fd = open(PIPE_PATH, O_CREAT | O_WRONLY);
    if (pipe_fd < 0)
        return catch();

    printf("Channel has opened, write your message:\n");

    char buf[1];
    while (buf[0] != NEXT_LINE)
    {
        read(STDIN_FILENO, buf, sizeof(buf));
        write(pipe_fd, buf, sizeof(buf));
    }
    
    close(pipe_fd);

    unlink(PIPE_PATH);

    printf("\n==== question 6 end ====\n");

    return 0;
}

int q6receive() {
    int pipe_fd = open(PIPE_PATH, O_RDONLY);
    if (pipe_fd < 0)
        return catch();

    printf("Message received from channel:\n");

    char buf[1];
    while (read(pipe_fd, buf, sizeof(buf)) > 0)
        write(STDOUT_FILENO, buf, sizeof(buf));

    close(pipe_fd);

    unlink(PIPE_PATH);

    return 0;
}

int q6_non_blocking()
{
    printf("=== question 6 start ===\n\n");

    char* message = NULL;
    size_t message_size;

    int pipe_fd = open(PIPE_PATH, O_WRONLY | O_NONBLOCK);
    if (pipe_fd < 0)
        return catch();

    printf("Channel has opened, write your message:\n");

    char buf[1];
    while (buf[0] != NEXT_LINE)
    {
        read(STDIN_FILENO, buf, sizeof(buf));
        write(pipe_fd, buf, sizeof(buf));
    }

    close(pipe_fd);

    unlink(PIPE_PATH);

    printf("\n==== question 6 end ====\n");

    return 0;
}

int q6receive2() {
    if (mkfifo(PIPE_PATH, 0666) < 0)
        return catch();
    
    int pipe_fd = open(PIPE_PATH, O_CREAT | O_RDONLY | O_NONBLOCK);
    if (pipe_fd < 0)
        return catch();

    printf("Message received from channel:\n");

    char buf[1];
    while (read(pipe_fd, buf, sizeof(buf)) <= 0) {}
    write(STDOUT_FILENO, buf, sizeof(buf));

    while (read(pipe_fd, buf, sizeof(buf)) > 0)
        write(STDOUT_FILENO, buf, sizeof(buf));

    close(pipe_fd);

    unlink(PIPE_PATH);

    return 0;
}