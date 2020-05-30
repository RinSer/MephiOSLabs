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
                
                get_P(qid);

                send_to_queue(qid, M, MSG_TO);

                struct game_message msg;
                msgrcv(qid, &msg, sizeof(msg), MSG_FROM, NULL);

                wipe_queue(qid);

                int P = atoi(msg.payload);
                printf("Child %d got P=%d\n", i, P);

                send_stream_to_port(ppid + 1, ++P);

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



void get_P(int qid)
{
    char buffer[MAXSIZE];
    struct game_message msg;
    int pid = getpid();
    for (int i = 0; i < 3; i++)
    {
        if (fork() < 0)
            return catch();

        if (pid != getpid())
        {
            if (i == 0)
            {
                msgrcv(qid, &msg, sizeof(msg), MSG_TO, NULL);

                int m = atoi(msg.payload);

                printf("Inner child %d got M=%d\n", i, m);

                send_to_queue(qid, ++m, MSG_FROM);

                exit(0);
            }
            else
            {
                exit(0);
            }
        }
    }
}