#include <game.h>

int get_from_shm(int shmid)
{
    sem_num* sem_number;
    
    sem_number = (sem_num*)shmat(shmid, (void*)0, 0);

    sem_init(&sem_number->semaphore, 1, 0);

    sem_wait(&sem_number->semaphore);

    int number = sem_number->number;

    sem_number->number = -3;

    sem_destroy(&sem_number->semaphore);

    shmdt(sem_number);
    
    catch("Error getting from shm");

    return number;
}

void send_to_shm(int shmid, int number)
{
    sem_num* sem_number = (sem_num*)shmat(shmid, (void*)0, 0);

    sem_number->number = number;

    while (sem_number->number != -3) 
        sem_post(&sem_number->semaphore);

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