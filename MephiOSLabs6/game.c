#include <game.h>

/*
Файл, из которого начальный процесс создает составляющие кольца.
*/

void game_handler(int signum);
int game(int argc, char* argv[])
{
    signal(SIGINT, game_handler);
    
    if (argc < 3) 
    {
        printf("\nShould receive 3 arguments:\n");
        printf("N = number of processes in the main ring\n");
        printf("M = initial number sent to child process\n");
        printf("L = limit score\n");

        return -1;
    }

    int N = atoi(argv[0]);
    int M = atoi(argv[1]);
    int L = atoi(argv[2]);

    printf("Starting game N=%d, M=%d, L=%d\n", N, M, L);

    int ppid = getpid();

    for (int i = 0; i < N; i++)
    {
        int cpid = fork();
        if (cpid < 0)
            return catch("Error forking in outer ring");

        if (cpid == 0)
        {
            if (i == 0)
                M = get_udp_from_port(ppid);
            else
                M = get_stream_from_port(ppid + i);
            int score = 0;
            for (;;)
            {
                int pid = getpid();

                printf("Child %d PID=%d got M=%d\n", i, pid, M);

                int P = get_P(M, L);

                printf("Child %d PID=%d got P=%d\n", i, pid, P);

                int Q = M - P;

                if (Q <= 0)
                {
                    if (++score >= L)
                    {
                        send_udp_to_port(ppid, getpid());

                        exit(0);
                    }
                    printf("Child %d PID=%d got score=%d\n", i, pid, score);
                }
                else M = Q;

                send_stream_to_port(ppid + ((i + 1) % N), M);

                M = get_stream_from_port(ppid + i);
            }
        }
    }

    if (ppid == getpid())
    {
        send_udp_to_port(ppid, M);

        int winner_pid = get_udp_from_port(ppid);

        printf("Winner process has PID=%d\n", winner_pid);

        kill(0, SIGKILL);
    }

    return 0;
}

void game_handler(int signum)
{
    kill(0, signum);
}

void get_P_handler(int signum);
int get_P(int M, int L)
{
    signal(SIGINT, get_P_handler);
    
    int qid = make_queue();

    send_to_queue(qid, M, MSG_TO);

    inner_ring(qid, L);

    int P = get_from_queue(qid, MSG_FROM);

    wipe_queue(qid);

    return P;
}

void get_P_handler(int signum)
{
    char queue_file_path[12];
    sprintf(queue_file_path, "%d", getpid());
    key_t msg_key = ftok(queue_file_path, 1);
    int qid = msgget(msg_key, 0666 | IPC_CREAT);
    msgctl(qid, IPC_RMID, NULL);
    unlink(queue_file_path);

    for (int i = 0; i < 3; i++)
    {
        char shm_file_path[16];
        sprintf(shm_file_path, "shm_%d", i);
        key_t key = ftok(shm_file_path, 25);
        int shmid = shmget(key, MAXSIZE, 0666 | IPC_CREAT);
        shmctl(shmid, IPC_RMID, NULL < 0);
        unlink(shm_file_path);
    }

    kill(0, SIGKILL);
}

extern int errno;
void inner_ring(int qid, int L)
{
    int ppid = getpid();
    int score = 0;
    int Q, shmid;
    int num_procs = 3;

    int shm_ids[3];
    for (int i = 0; i < num_procs; i++)
    {
        shm_ids[i] = make_shm(i);
        send_to_shm(shm_ids[i], -1);
    }

    int cpids[num_procs];
    for (int i = 0; i < num_procs; i++)
    {
        int cpid = fork();
        if (cpid < 0)
            return catch("Error forking in inner ring");
        else if (cpid > 0)
            cpids[i] = cpid;
        else
        {
            if (i == 0)
                Q = get_from_queue(qid, MSG_TO);
            else
                Q = get_from_shm(shm_ids[i]);
            for (;;)
            {
                if (--Q <= 0)
                {
                    if (++score >= L)
                    {
                        printf("Inner child %d PID=%d got score=%d\n", i, getpid(), score);
                        send_to_queue(qid, getpid(), MSG_FROM);
                        exit(0);
                    }
                    Q++;
                }
                send_to_shm(shm_ids[i], -1);
                send_to_shm(shm_ids[(i + 1) % num_procs], Q);
                Q = get_from_shm(shm_ids[i]);
            }
        }
    }
    
    if (ppid == getpid())
    {
        while (wait(NULL) > 0);
        errno = 0;
        for (int i = 0; i < num_procs; i++)
        {
            if (kill(cpids[i], SIGKILL) < 0) errno = 0;
            wipe_shm(shm_ids[i], i);
        }
    }
}