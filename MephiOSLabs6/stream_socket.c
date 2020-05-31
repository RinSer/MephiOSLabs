#include <game.h>

int get_stream_from_port(int port)
{
    int server_fd, new_socket, valread;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0
        || setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &(int){1}, sizeof(int)))
        return catch();

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address,
        sizeof(address)) < 0 || listen(server_fd, 3) < 0
        || (new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
        return catch();

    char buffer[MAXSIZE];
    read(new_socket, buffer, MAXSIZE);

    return atoi(buffer);
}

send_stream_to_port(int port, int number)
{
    printf("%d %d\n", port, number);
    int sock = 0, valread;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return catch();
    printf("%d", socket);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        return catch();

    char buffer[MAXSIZE];
    sprintf(buffer, "%d", number);
    printf("%s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);
}