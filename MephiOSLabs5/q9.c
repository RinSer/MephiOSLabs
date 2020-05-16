#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
Добавить использование слабой блокировки во второй. Что изменится?
*/

int q9(char* file_path)
{
    printf("=== question 9 start ===\n\n");

    int fd;
    char buff[1];
    int child_pid = fork();

    if (child_pid < 0)
        return catch();

    struct flock weak_lock;

    weak_lock.l_start = 0;
    weak_lock.l_whence = SEEK_SET;
    weak_lock.l_len = 0;

    if (child_pid > 0)
    {
        weak_lock.l_type = F_RDLCK;
        weak_lock.l_pid = getpid();

        fd = open(file_path, O_RDONLY);
        if (fd < 0 || fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        while (read(fd, buff, sizeof(buff)) > 0)
            write(STDOUT_FILENO, buff, sizeof(buff));

        weak_lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        close(fd);
    }
    else
    {
        usleep(1);
        
        weak_lock.l_type = F_WRLCK;
        weak_lock.l_pid = getpid();
        
        fd = open(file_path, O_WRONLY);
        if (fd < 0 || fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        char test_line[] = "Write something to the file\n";

        write(fd, test_line, sizeof(test_line) - 1);

        weak_lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        close(fd);

        exit(0);
    }

    printf("\n==== question 9 end ====\n");

    return 0;
}

int q9_lock_check(char* file_path)
{
    printf("=== question 9 start ===\n\n");

    int fd;
    char buff[1];
    int child_pid = fork();

    if (child_pid < 0)
        return catch();

    struct flock weak_lock, check_lock;

    weak_lock.l_start = 0;
    weak_lock.l_whence = SEEK_SET;
    weak_lock.l_len = 0;

    if (child_pid > 0)
    {
        weak_lock.l_type = F_RDLCK;
        weak_lock.l_pid = getpid();

        fd = open(file_path, O_RDONLY);
        if (fd < 0 || fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        if (fcntl(fd, F_GETLK, &check_lock) < 0)
            return catch();
        while (check_lock.l_type != F_UNLCK)
        {
            if (fcntl(fd, F_GETLK, &check_lock) < 0)
                return catch();
        }

        while (read(fd, buff, sizeof(buff)) > 0)
            write(STDOUT_FILENO, buff, sizeof(buff));

        weak_lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        close(fd);
    }
    else
    {
        //usleep(1);

        weak_lock.l_type = F_WRLCK;
        weak_lock.l_pid = getpid();

        fd = open(file_path, O_WRONLY);
        if (fd < 0 || fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        if (fcntl(fd, F_GETLK, &check_lock) < 0)
            return catch();
        while (check_lock.l_type != F_UNLCK)
        {
            if (fcntl(fd, F_GETLK, &check_lock) < 0)
                return catch();
        }

        char test_line[] = "Write something to the file\n";

        write(fd, test_line, sizeof(test_line) - 1);

        weak_lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &weak_lock) < 0)
            return catch();

        close(fd);

        exit(0);
    }

    printf("\n==== question 9 end ====\n");

    return 0;
}