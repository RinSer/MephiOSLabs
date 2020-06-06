#include <game.h>

int make_queue()
{
    char queue_file_path[12];
    sprintf(queue_file_path, "%d", getpid());
    FILE* fp = fopen(queue_file_path, "w+");
    fclose(fp);

    key_t msg_key = ftok(queue_file_path, 1);

    int qid = msgget(msg_key, 0666 | IPC_CREAT);

    catch("Error making queue");

    return qid;
}

int wipe_queue(int qid)
{
    char queue_file_path[12];
    sprintf(queue_file_path, "%d", getpid());

    msgctl(qid, IPC_RMID, NULL);

    unlink(queue_file_path);

    catch("Error wiping queue");
}

int get_from_queue(int qid, int type)
{
    game_message* msg = malloc(sizeof(game_message));
    msgrcv(qid, msg, sizeof(game_message), type, NULL);
    int number = atoi(msg->payload);
    free(msg);
    return number;
}

void send_to_queue(int qid, int number, int type)
{
    struct msqid_ds* queue_stats = malloc(sizeof(struct msqid_ds));
    msgctl(qid, IPC_STAT, queue_stats);
    int num_messages = queue_stats->msg_qnum;

    game_message* msg = malloc(sizeof(game_message));
    sprintf(msg->payload, "%d", number);
    msg->type = type;
    msgsnd(qid, msg, sizeof(game_message), NULL);

    msgctl(qid, IPC_STAT, queue_stats);
    int num_messages_after = queue_stats->msg_qnum;
    while (num_messages == num_messages_after)
    {
        msgsnd(qid, msg, sizeof(game_message), NULL);
        msgctl(qid, IPC_STAT, queue_stats);
        int num_messages_after = queue_stats->msg_qnum;
    }

    free(msg);
    free(queue_stats);

    catch("Error sending to queue");
}