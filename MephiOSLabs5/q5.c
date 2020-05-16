#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

/*
Написать программу, позволяющую удалять очереди сообщений по идентификатору. 
Обработать возможные ошибочные ситуации.
*/

int q5(char* arg)
{
    if (arg == NULL)
    {
        printf("Should get params Queue ID!\n");
        return -1;
    }

    int qid = atoi(arg);

    if (msgctl(qid, IPC_RMID, NULL) < 0)
        return catch();

    printf("Have successfully closed Queue with ID %d\n", qid);

    return 0;
}