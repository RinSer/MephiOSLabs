#include <game.h>

int make_queue()
{
    char queue_file_path[12];
    sprintf(queue_file_path, "%d", getpid());
    FILE* fp = fopen(queue_file_path, "w+");
    if (fclose(fp) < 0)
        return catch();

    key_t msg_key = ftok(queue_file_path, 1);
    if ((int)msg_key < 0) return catch();

    int qid = msgget(msg_key, 0666 | IPC_CREAT);
    if (qid < 0) return catch();

    return qid;
}

int wipe_queue(int qid)
{
    char queue_file_path[12];
    sprintf(queue_file_path, "%d", getpid());

    if (msgctl(qid, IPC_RMID, NULL) < 0)
        return catch();

    if (unlink(queue_file_path) < 0)
        return catch();
}

int get_from_queue(int qid, int type)
{
    struct game_message* msg = malloc(sizeof(struct game_message));
    msgrcv(qid, msg, sizeof(struct game_message), type, NULL);
    int number = atoi(msg->payload);
    free(msg);
    return number;
}

void send_to_queue(int qid, int number, int type)
{
    struct game_message* msg = malloc(sizeof(struct game_message));
    sprintf(msg->payload, "%d", number);
    msg->type = type;
    if (msgsnd(qid, msg, sizeof(struct game_message), NULL) < 0)
        return catch();
    free(msg);
}