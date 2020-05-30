/*
    Точка входа для запуска файлов с решениями
*/

int main(int argc, char* argv[], char* env[])
{
    ring_game(argc - 1, &argv[1]);

    //printf("%d\n", get_P(12));

    return 0;
}