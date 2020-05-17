#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <cshelper.h>

/*
6. Написать программы для работы с очередями сообщений в соответствии с моделью клиент-сервер: 
каждый процесс использует собственную очередь сообщений. 
Процесс-сервер читает запросы из своей очереди сообщений и посылает ответ процессам-клиентам в их очереди. 
Процессы-клиенты читают ответ и выводят его в выходной поток. 
Процессы-клиенты должны передавать процессу-серверу информацию о своих очередях сообщений (куда записывать ответ).
+
7. Осуществить при помощи программ п. 6. обмен сообщениями между несколькими пользователями, при условии, 
что каждому пользователю предназначены сообщения любого или определенного типа (по договоренности). 
Будут ли примеры с очередями сообщений "приводить себя в порядок"? 
Что произойдет, если прервать процесс-сервер с помощью клавиши CTRL-C?
+
9. Модифицировать программы п. 6 так, чтобы использовались две очереди: 
одна для запросов к серверу и одна для всех ответов от сервера к любому клиенту.
*/

int q6_client()
{
    int pid = getpid();
    char client_queue[12];
    sprintf(client_queue, "%d", pid);
    FILE * fp = fopen(client_queue, "w+");
    fclose(fp);
    
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
    int qid_rcv = open_queue(SERVER_MSGQ);

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

int open_queue(char* path)
{
    key_t msg_key = ftok(path, CS_PROJECT_ID);
    if (msg_key < 0) return catch();

    int qid = msgget(msg_key, 0666 | IPC_CREAT);
    if (qid < 0) return catch();

    return qid;
}