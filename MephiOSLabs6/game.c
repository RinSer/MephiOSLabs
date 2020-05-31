#include <game.h>

/*
Файл, из которого начальный процесс создает составляющие кольца.
*/

int game(int argc, char* argv[])
{
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
        if (fork() < 0)
            return catch();

        if (ppid != getpid())
        {
            if (i == 0)
            {
                int M = get_udp_from_port(ppid);

                printf("Child %d got M=%d\n", i, M);
                
                int qid = make_queue();

                send_to_queue(qid, M, MSG_TO);
                
                get_P(qid, L);

                M = get_from_queue(qid, MSG_FROM);

                wipe_queue(qid);

                printf("Child %d got P=%d\n", i, M);

                send_stream_to_port(ppid + 1, ++M);

                M = get_stream_from_port(ppid);

                printf("Child %d got M=%d\n", i, M);
                
                send_udp_to_port(ppid, getpid());

                exit(0);
            }
            else
            {
                int M = get_stream_from_port(ppid + i);

                printf("Child %d got M=%d\n", i, M);
                sleep(1);
                
                send_stream_to_port(ppid + ((i + 1) % N), ++M);

                exit(0);
            }
        }
    }

    if (ppid == getpid())
    {
        send_udp_to_port(ppid, M);

        int winner_pid = get_udp_from_port(ppid);

        printf("Winner process has PID=%d\n", winner_pid);
    }

    return 0;
}

void get_P(int qid, int L)
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

    for (int i = 0; i < num_procs; i++)
    {
        int cpid = fork();
        if (cpid < 0)
            return catch();

        if (ppid != getpid())
        {
            if (i == 0)
                Q = get_from_queue(qid, MSG_TO);
            else
                Q = get_from_shm(shm_ids[i]);
            for (;;)
            {
                if (--Q <= 0)
                {
                    if (++score == L)
                    {
                        printf("Inner child %d has Q=%d\n", getpid(), Q);
                        send_to_queue(qid, getpid(), MSG_FROM);
                        exit(0);
                    }
                    Q++;
                }
                send_to_shm(shm_ids[(i + 1) % num_procs], Q);
                Q = get_from_shm(shm_ids[i]);
            }
        }
    }
    
    if (ppid == getpid())
    {
        while (wait(NULL) > 0) {}
        for (int i = 0; i < num_procs; i++)
            wipe_shm(shm_ids[i], i);
    }
}