#include <game.h>

int get_udp_from_port(int port)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr));

    int len = sizeof(cliaddr);
    char buffer[MAXSIZE];
    int n = recvfrom(sockfd, (char*)buffer, MAXSIZE, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
    buffer[n] = '\0';

    sendto(sockfd, (const char*)buffer, sizeof(buffer), MSG_CONFIRM,
        (const struct sockaddr*)&cliaddr, sizeof(servaddr));

    close(sockfd);

    catch("Error from get udp port");

    return atoi(buffer);
}

extern int errno;
void send_udp_to_port(int port, int number)
{
    int sockfd, len, n;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    char buffer[MAXSIZE];
    sprintf(buffer, "%d", number);
    sendto(sockfd, (const char*)buffer, sizeof(buffer), MSG_CONFIRM,
        (const struct sockaddr*)&servaddr, sizeof(servaddr));

    while (recvfrom(sockfd, (char*)buffer, MAXSIZE, MSG_DONTWAIT, (struct sockaddr*)&servaddr, &len) < 0)
        sendto(sockfd, (const char*)buffer, sizeof(buffer), MSG_CONFIRM,
            (const struct sockaddr*)&servaddr, sizeof(servaddr));
    errno = 0;

    close(sockfd);

    catch("Error from send udp to port");
}