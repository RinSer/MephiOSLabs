#include <game.h>

int get_from_shm(int shmid, int sem_id, int idx)
{
    sem_num* sem_number;
    
    sem_number = (sem_num*)shmat(shmid, (void*)0, 0);
    catch ("Error getting from shm shmat");

    struct sembuf sops[2];
    sops[0].sem_num = idx;
    sops[0].sem_op = 0;
    sops[0].sem_flg = 0;
    sops[1].sem_num = idx;
    sops[1].sem_op = 1;
    sops[1].sem_flg = 0;

    semop(sem_id, sops, 2);
    catch ("Error getting from shm semop");

    int number = sem_number->number;

    shmdt(sem_number);
    
    catch("Error getting from shm");

    return number;
}

void send_to_shm(int shmid, int number, int sem_id, int idx)
{
    sem_num* sem_number = (sem_num*)shmat(shmid, (void*)0, 0);
    catch("Error connecting to shm\n");

    sem_number->number = number;

    union semun {
        int val;
        struct semid_ds* buf;
        ushort * array;
    } arg;

    arg.val = 0;
    semctl(sem_id, idx, SETVAL, arg);
    catch("Error semctl\n");

    shmdt(sem_number);

    catch("Error sending to shm");
}

int make_shm(int file_id)
{
    char shm_file_path[16];
    sprintf(shm_file_path, "shm_%d", file_id);
    FILE* fp = fopen(shm_file_path, "w+");
    fclose(fp);

    key_t key = ftok(shm_file_path, 25);

    int shmid = shmget(key, MAXSIZE, 0666 | IPC_CREAT);

    catch("Error making shm");

    return shmid;
}

void wipe_shm(int shmid, int file_id)
{
    shmctl(shmid, IPC_RMID, NULL < 0);

    char shm_file_path[16];
    sprintf(shm_file_path, "shm_%d", file_id);

    unlink(shm_file_path);

    catch("Error wiping shm");
}