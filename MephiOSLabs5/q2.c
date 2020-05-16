#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <qhelper.h>

/*
Написать программу, позволяющую читать сообщения из очереди и выводить их на экран. 
Идентификатор очереди и тип сообщения передается через аргументы командной строки.
*/

int q2_receive(char* arg1, char* arg2)
{
    if (arg1 == NULL || arg2 == NULL)
    {
        printf("Should get params Queue ID and Message type!\n");
        return -1;
    }
    
    int qid = atoi(arg1);
    int rcv_type = atoi(arg2);
    struct message_4q msg;

    printf("\nGet messages from the queue:\n");
    while (msgrcv(qid, &msg, sizeof(msg), rcv_type, NULL) > 0)
        printf("%s received with type %d\n", msg.payload, (int)msg.type);

    return 0;
}

int q2_send()
{
    int pid = getpid();
    key_t msg_key = ftok(MMSGQP, pid);
    if (msg_key < 0) return catch();

    int qid = msgget(msg_key, 0666 | IPC_CREAT);
    if (qid < 0) return catch();

    printf("Have opened the queue with ID %d\n", qid);

    int snd_types[MSG_NUM] = { 1, 1, 2, 2, 3, 3 };
    for (int i = 0; i < MSG_NUM; i++)
    {
        char msg[MSG_SIZE];
        sprintf(&msg, "Message%d", i);
        struct message_4q message;
        message.type = snd_types[i];
        strcpy(message.payload, msg);
        if (msgsnd(qid, &message, sizeof(message), IPC_NOWAIT) < 0)
            return catch();
        printf("Have sent message with type %d\n", snd_types[i]);
    }

    printf("Have sent all messages!\n");
}