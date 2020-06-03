#include <game.h>

/*
Функция для ловли ошибок
*/

extern int errno;
int catch(char* message)
{
    if (errno > 0)
    {
        perror(message);
        kill(0, SIGINT);
        return -1;
    }
    return 0;
}

void suppress()
{
    errno = 0;
}