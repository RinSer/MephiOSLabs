#include <game.h>

int get_from_shm(int id)
{
    char shm_file_path[16];
    sprintf(shm_file_path, "shm_%d", getpid());

    key_t key = ftok("shmfile", 65);
    if ((int)key < 0) return catch();

    int shmid = shmget(key, MAXSIZE, 0666 | IPC_CREAT);
    if (shmid < 0) return catch();

    char* str_number = (char*)shmat(shmid, (void*)0, 0);
    int number = atoi(str_number);

    if (shmdt(str_number) < 0 || shmctl(shmid, IPC_RMID, NULL < 0))
        return catch();

    if (unlink(shm_file_path) < 0)
        return catch();

    return number;
}

void send_to_shm(int id, int number)
{
    char shm_file_path[16];
    sprintf(shm_file_path, "shm_%d", getpid());
    FILE* fp = fopen(shm_file_path, "w+");
    if (fclose(fp) < 0) catch();
    
    key_t key = ftok("shmfile", 65);
    if ((int)key < 0) catch();

    int shmid = shmget(key, MAXSIZE, 0666 | IPC_CREAT);
    if (shmid < 0) catch();

    char* str_number = (char*)shmat(shmid, (void*)0, 0);

    sprintf(&str_number, "%d", number);

    if (shmdt(str_number) < 0) catch();
}