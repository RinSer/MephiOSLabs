#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <cshelper.h>

/*
Еще раз модифицировать эти программы так, 
чтобы использовалась только одна очередь сообщений и для запросов к серверу, 
и для всех ответов.
*/

void client_inter(int _);
void server_inter(int _);

int q10_client()
{
    int pid = getpid();

    int qid = open_queue(SERVER_MSGQ);

    signal(SIGINT, client_inter);

    struct message_cs msg;

    msg.type = qid;

    char buff[37];
    sprintf(buff, "%d I am your new client!", pid);
    strcpy(msg.payload, buff);

    msgsnd(qid, &msg, sizeof(msg), NULL);

    while (msgrcv(qid, &msg, sizeof(msg), pid, NULL) > 0)
    {
        printf("Message from Server: %s\n", msg.payload);

        msg.type = qid;

        sprintf(buff, "%d Client is still alive...", pid);
        strcpy(msg.payload, buff);

        msgsnd(qid, &msg, sizeof(msg), NULL);
    }

    printf("Server has closed the queue!\n");

    return 0;
}

int q10_server()
{
    int qid = open_queue(SERVER_MSGQ);

    signal(SIGINT, server_inter);

    struct message_cs msg;

    while (msgrcv(qid, &msg, sizeof(msg), qid, NULL) > 0)
    {
        printf("Message received from Client: %s\n", msg.payload);

        int idx = strchr(msg.payload, ' ') - msg.payload;
        msg.payload[idx] = 0;
        msg.type = atoi(msg.payload);

        char msg_buff[CS_MSG_SIZE];
        sprintf(msg_buff, "Hi, dear Client with PID %d!", (int)msg.type);
        strcpy(msg.payload, msg_buff);

        msgsnd(qid, &msg, sizeof(msg), NULL);
    }
}

void client_inter(int _)
{
    int qid = open_queue(SERVER_MSGQ);

    struct message_cs msg;

    msg.type = getpid();

    char buff[37];
    sprintf(buff, "Client %d has been interrupted...", getpid());
    strcpy(msg.payload, buff);

    msgsnd(qid, &msg, sizeof(msg), NULL);

    exit(0);
}

void server_inter(int _)
{
    int qid = open_queue(SERVER_MSGQ);

    struct message_cs msg;

    while (msgrcv(qid, &msg, sizeof(msg), qid, IPC_NOWAIT) > 0)
        printf("Message received from Client: %s\n", msg.payload);

    if (msgctl(qid, IPC_RMID, NULL) < 0)
        return catch();

    printf("Server has closed the queue and finished!\n");

    exit(0);
}