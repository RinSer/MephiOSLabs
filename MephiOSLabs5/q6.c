#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <qhelper.h>

/*
Написать программы для работы с очередями сообщений в соответствии с моделью клиент-сервер: 
каждый процесс использует собственную очередь сообщений. 
Процесс-сервер читает запросы из своей очереди сообщений и посылает ответ процессам-клиентам в их очереди. 
Процессы-клиенты читают ответ и выводят его в выходной поток. 
Процессы-клиенты должны передавать процессу-серверу информацию о своих очередях сообщений (куда записывать ответ).
*/

#define SERVER_MSGQ  "server_message_queue"
#define CS_MSG_SIZE 100
#define CS_PROJECT_ID 25

typedef struct message_cs {
    long type;
    char payload[CS_MSG_SIZE];
};

int q6_client()
{
    int pid = getpid();
    char client_queue[12];
    sprintf(client_queue, "%d", pid);
    int fd = fopen(client_queue, "w+");
    if (fd < 0) return catch();
    close(fd);
    
    int qid_snd = open_queue(SERVER_MSGQ);
    int qid_rcv = open_queue(client_queue);
    
    struct message_cs msg;
    msg.type = qid_rcv;
    strcpy(msg.payload, "I am your new client!");

    msgsnd(qid_snd, &msg, sizeof(msg), NULL);

    while (msgrcv(qid_rcv, &msg, sizeof(msg), qid_rcv, NULL) > 0)
    {
        printf("Message from Server: %s\n", msg.payload);
        char buff[37];
        sprintf(buff, "Client %d is still alive...", pid);
        strcpy(msg.payload, buff);
        msgsnd(qid_snd, &msg, sizeof(msg), NULL);
    }

    return 0;
}

int q6_server()
{
    int size = 0;
    int* clients = malloc(size * sizeof(int));

    int qid_rcv = open_queue(SERVER_MSGQ);

    struct message_cs msg;

    while (msgrcv(qid_rcv, &msg, sizeof(msg), 0, NULL) > 0)
    {
        int client_type = msg.type;
        int client_idx = contains(clients, size, client_type);
        if (client_idx == -1)
        {
            realloc(clients, size + 1);
            clients[size] = client_type;
            size++;
        }
        printf("Message received from Client: %s\n", msg.payload);
        char msg_buff[CS_MSG_SIZE];
        sprintf(msg_buff, "Hi, dear Client with Queue Id %d!", client_type);
        strcpy(msg.payload, msg_buff);
        msgsnd((int)msg.type, &msg, sizeof(msg), NULL);
    }
}

int contains(int* array, int size, int value)
{
    for (int i = 0; i < size; i++)
        if (array[i] == value) return i;
    return -1;
}

int open_queue(char* path)
{
    key_t msg_key = ftok(path, CS_PROJECT_ID);
    if (msg_key < 0) return catch();

    int qid = msgget(msg_key, 0666 | IPC_CREAT);
    if (qid < 0) return catch();

    return qid;
}