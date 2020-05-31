#include <game.h>

/*
    Точка входа для запуска файлов с решениями
*/

int main(int argc, char* argv[], char* env[])
{
    ring_game(argc - 1, &argv[1]);

    /*int qid = make_queue();

    get_P(qid, 10);

    send_to_queue(qid, 100, MSG_TO);

    struct game_message msg;
    msgrcv(qid, &msg, sizeof(msg), MSG_FROM, NULL);

    wipe_queue(qid);*/

    return 0;
}