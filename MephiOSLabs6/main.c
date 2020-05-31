#include <game.h>

/*
    Точка входа для запуска файлов с решениями
*/

int main(int argc, char* argv[], char* env[])
{
    game(argc - 1, &argv[1]);

    /*int qid = make_queue();

    send_to_queue(qid, 2, MSG_TO);

    get_P(qid, 10);

    printf("%d\n", get_from_queue(qid, MSG_FROM));

    wipe_queue(qid);*/

    return 0;
}