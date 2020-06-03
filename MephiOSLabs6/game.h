#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define MAXSIZE 1024 
#define ZERO_PORT 5000

#define MSG_TO 1
#define MSG_FROM 2

typedef struct game_message {
    long type;
    char payload[MAXSIZE];
};

typedef struct {
    sem_t semaphore;
    int number;
} SemNumber;