#include <game.h>

int get_udp_from_port(int port)
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0
        || setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        return catch();

    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        return catch();

    int len = sizeof(cliaddr);
    char buffer[MAXSIZE];
    int n = recvfrom(sockfd, (char*)buffer, MAXSIZE, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
    buffer[n] = '\0';

    close(sockfd);

    return atoi(buffer);
}

void send_udp_to_port(int port, int number)
{
    int sockfd, len, n;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return catch();

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    char buffer[MAXSIZE];
    sprintf(buffer, "%d", number);
    sendto(sockfd, (const char*)buffer, sizeof(buffer), MSG_CONFIRM,
        (const struct sockaddr*)&servaddr, sizeof(servaddr));

    close(sockfd);
}