#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <qhelper.h>

/*
Написать программу, 
иллюстрирующую возможность синхронизации процессов при помощи очередей сообщений.
*/

#define MSG_TYPE 1

typedef struct message {
    long type;
    char payload[32];
};

int q11()
{
    key_t msg_key = ftok(MMSGQP, getpid());
    if (msg_key < 0) return catch();

    int qid = msgget(msg_key, 0666 | IPC_CREAT);
    if (qid < 0) return catch();

    int chpid = fork();
    if (chpid < 0) 
        return catch();

    struct message msg;

    if (chpid > 0)
    {
        if (msgrcv(qid, &msg, sizeof(msg), MSG_TYPE, NULL) < 0)
            return catch();

        printf("%s", msg.payload);

        if (msgctl(qid, IPC_RMID, NULL) < 0)
            return catch();
    }
    else
    {
        for (int i = 0; i < 100; i++)
            printf("Child is working...\n", i);

        msg.type = MSG_TYPE;

        strcpy(msg.payload, "Dear Parent, I have finished!\n");
        if (msgsnd(qid, &msg, sizeof(msg), NULL) < 0)
            return catch();
    }

    return 0;
}