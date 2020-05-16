#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <qhelper.h>

/*
Создать очередь сообщений или получить доступ к уже существующей очереди. 
Вывести на экран статистическую информацию об очереди сообщений. 
Поместить несколько сообщений различных типов в очередь.
*/

int q1()
{
    printf("\n=== question 1 start ===\n\n");
    
    int pid = getpid();
    key_t msg_key = ftok(MMSGQP, pid);
    if (msg_key < 0) return catch();

    int qid = msgget(msg_key, 0666 | IPC_CREAT);
    if (qid < 0) return catch();

    printf("Statistics from empty queue:\n");
    print_queue_stats(qid);

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
    }

    printf("\nStatistics from queue with messages:\n");
    print_queue_stats(qid);

    printf("\nGet messages back from the queue:\n");
    int rcv_types[MSG_NUM] = { 1, 2, 3, 1, 2, 3 };
    for (int i = 0; i < MSG_NUM; i++)
    {
        struct message_4q msg;
        if (msgrcv(qid, &msg, sizeof(msg), rcv_types[i], IPC_NOWAIT) < 0)
            return catch();
        printf("%s received with type %d\n", msg.payload, (int)msg.type);
    }

    printf("\nStatistics from queue without messages:\n");
    print_queue_stats(qid);

    if (msgctl(qid, IPC_RMID, NULL) < 0)
        return catch();

    printf("\n==== question 1 end ====\n");

    return 0;
}

/*
    Выводит статистическую информацию об очереди сообщений
*/
void print_queue_stats(int qid) 
{
    struct msqid_ds queue_stats;
    if (msgctl(qid, IPC_STAT, &queue_stats) < 0)
        catch();

    printf("Queue's owner id: %d\n", queue_stats.msg_perm.uid);
    printf("Time of the last sent message: %s", ctime(&queue_stats.msg_stime));
    printf("Time of the last received message: %s", ctime(&queue_stats.msg_rtime));
    printf("Time of the last change in the queue %s", ctime(&queue_stats.msg_ctime));
    printf("Number of bytes in the queue: %lu\n", queue_stats.__msg_cbytes);
    printf("Number of messages in the queue: %lu\n", queue_stats.msg_qnum);
    printf("Maximum number of bytes allowed in the queue: %lu\n", queue_stats.msg_qbytes);
    printf("PID of process that last sent message to the queue: %d\n", queue_stats.msg_lspid);
    printf("PID of process that last received message form the queue: %d\n", queue_stats.msg_lrpid);
}