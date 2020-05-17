#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <cshelper.h>

/*
Модифицировать программы п. 6 так, 
чтобы они завершались корректно и в случае прерывания по CTRL-C.
*/

void client_int(int _);
void server_int(int _);

int q8_client()
{
    int pid = getpid();
    char client_queue[12];
    sprintf(client_queue, "%d", pid);
    FILE * fp = fopen(client_queue, "w+");
    fclose(fp);

    int qid_snd = open_queue(SERVER_MSGQ);
    int qid_rcv = open_queue(client_queue);

    signal(SIGINT, client_int);

    struct message_cs msg;
    msg.type = qid_rcv;
    strcpy(msg.payload, "I am your new client!");

    msgsnd(qid_snd, &msg, sizeof(msg), NULL);

    bool server_is_receiving = true;
    while (server_is_receiving)
    {
        if (msgrcv(qid_rcv, &msg, sizeof(msg), qid_rcv, IPC_NOWAIT) > 0)
            printf("Message from Server: %s\n", msg.payload);
        else sleep(1);
        char buff[37];
        sprintf(buff, "Client %d is still alive...", pid);
        strcpy(msg.payload, buff);
        if (msgsnd(qid_snd, &msg, sizeof(msg), NULL) < 0)
            server_is_receiving = false;
    }

    if (msgctl(qid_rcv, IPC_RMID, NULL) < 0)
        return catch();

    sprintf(client_queue, "%d", pid);
    if (unlink(client_queue) < 0)
        return catch();

    printf("Server has closed the queue!\n");

    return 0;
}

int q8_server()
{
    int qid_rcv = open_queue(SERVER_MSGQ);

    signal(SIGINT, server_int);

    struct message_cs msg;

    while (msgrcv(qid_rcv, &msg, sizeof(msg), 0, NULL) > 0)
    {
        printf("Message received from Client: %s\n", msg.payload);
        char msg_buff[CS_MSG_SIZE];
        sprintf(msg_buff, "Hi, dear Client with Queue Id %d!", (int)msg.type);
        strcpy(msg.payload, msg_buff);
        msgsnd((int)msg.type, &msg, sizeof(msg), NULL);
    }
}

void client_int(int _)
{
    char client_queue[12];
    sprintf(client_queue, "%d", getpid());
    
    int qid_snd = open_queue(SERVER_MSGQ);
    int qid_rcv = open_queue(client_queue);
    
    struct message_cs msg;

    msg.type = qid_rcv;

    char buff[37];
    sprintf(buff, "Client %d has been interrupted...", getpid());
    strcpy(msg.payload, buff);

    if (msgsnd(qid_snd, &msg, sizeof(msg), NULL) < 0)
        if (msgctl(qid_snd, IPC_RMID, NULL) < 0)
            return catch ();

    if (msgctl(qid_rcv, IPC_RMID, NULL) < 0)
        return catch();

    sprintf(client_queue, "%d", getpid());
    if (unlink(client_queue) < 0)
        return catch();

    exit(0);
}

void server_int(int _)
{
    int qid_rcv = open_queue(SERVER_MSGQ);
    
    struct message_cs msg;

    while (msgrcv(qid_rcv, &msg, sizeof(msg), 0, IPC_NOWAIT) > 0)
        printf("Message received from Client: %s\n", msg.payload);

    if (msgctl(qid_rcv, IPC_RMID, NULL) < 0)
        return catch();

    printf("Server has closed the queue and finished!\n");

    exit(0);
}