#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXSIZE 1024 

#define MSG_TO 1
#define MSG_FROM 2

typedef struct game_message {
    long type;
    char payload[MAXSIZE];
};