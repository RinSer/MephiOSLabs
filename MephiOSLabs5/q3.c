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
позволив ей избежать ожидания в случае отсутствия в очереди сообщений данного типа.
*/

int q3(char* arg1, char* arg2)
{
    if (arg1 == NULL || arg2 == NULL)
    {
        printf("Should get params Queue ID and Message type!\n");
        return -1;
    }

    int qid = atoi(arg1);
    int rcv_type = atoi(arg2);
    struct message_4q *msg = malloc(sizeof(struct message_4q));

    printf("\nGet messages from the queue:\n");
    while (msgrcv(qid, msg, sizeof(struct message_4q), rcv_type, IPC_NOWAIT) > 0)
        printf("%s received with type %d\n", msg->payload, (int)msg->type);
    
    free(msg);

    try_close_queue(qid);

    return 0;
}

/*
    Удаляем очередь, если она пуста
*/
void try_close_queue(int qid)
{
    // close the queue if it is empty
    struct msqid_ds queue_stats;
    if (msgctl(qid, IPC_STAT, &queue_stats) < 0)
        catch();
    if ((int)queue_stats.msg_qnum == 0)
        if (msgctl(qid, IPC_RMID, NULL) < 0)
            catch();
}