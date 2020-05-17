#define SERVER_MSGQ  "server_message_queue"
#define CS_MSG_SIZE 100
#define CS_PROJECT_ID 25

typedef struct message_cs {
    long type;
    char payload[CS_MSG_SIZE];
};