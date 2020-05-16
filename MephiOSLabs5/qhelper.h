#define MMSGQP "my_message_queue"
#define MSG_SIZE 9
#define MSG_NUM 6

typedef struct message_4q {
    long type;
    char payload[MSG_SIZE];
};