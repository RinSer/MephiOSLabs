#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <qhelper.h>

/*
Модифицировать программу п. 2, 
позволив ей принимать первые несколько байтов сообщений произвольных размеров.
*/

#define MSG_BUFF_SIZE 0

typedef struct message_4q_q4 {
    long type;
    char payload[MSG_BUFF_SIZE];
};

int q4(char* arg1, char* arg2)
{
    if (arg1 == NULL || arg2 == NULL)
    {
        printf("Should get params Queue ID and Message type!\n");
        return -1;
    }

    int qid = atoi(arg1);
    int rcv_type = atoi(arg2);
    struct message_4q_q4* msg = malloc(sizeof(struct message_4q_q4));

    printf("\nGet messages from the queue:\n");
    while (msgrcv(qid, msg, sizeof(struct message_4q_q4), rcv_type, MSG_NOERROR | IPC_NOWAIT) > 0)
        printf("%s received with type %d\n", msg->payload, (int)msg->type);
    
    free(msg);

    try_close_queue(qid);

    return 0;
}