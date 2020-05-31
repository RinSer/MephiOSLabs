#include <game.h>

/*
Файл, из которого начальный процесс создает составляющие кольца.
*/

int ring_game(int argc, char* argv[])
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
                
                /*get_P(qid, 0);

                send_to_queue(qid, 0, MSG_TO);

                struct game_message msg;
                msgrcv(qid, &msg, sizeof(msg), MSG_FROM, NULL);

                wipe_queue(qid);

                M = atoi(msg.payload);*/
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
    struct game_message msg;
    int score = 0;
    int Q;
    int num_procs = 3;
    for (int i = 0; i < num_procs; i++)
    {
        int cpid = fork();
        if (cpid < 0)
            return catch();

        if (cpid == 0)
        {
            if (i == 0)
            {
                //send_to_shm((i + 1) % num_procs, 0);
                msgrcv(qid, &msg, sizeof(msg), MSG_TO, NULL);
                Q = atoi(msg.payload);
                printf("Inner child %d got Q=%d\n", i, Q);
            }
            else
            {
                //send_to_shm((i + 1) % num_procs, 0);
                //Q = get_from_shm(i);
                exit(0);
            }
            for (;;)
            {
                //printf("II Child %d got Q=%d\n", i, Q);
                if (--Q <= 0)
                {
                    if (++score == L)
                    {
                        send_to_queue(qid, getpid(), MSG_FROM);
                        exit(0);
                    }
                    Q++;
                }
                //send_to_shm((i + 1) % num_procs, Q);
                //Q = get_from_shm(i);
            }
        }
    }
}