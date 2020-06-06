#include <game.h>

int get_stream_from_port(int port)
{
    int sfd, connection;

    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0
        || setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &(int){1}, sizeof(int)))
        catch("Error opening server stream socket");

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sfd, (struct sockaddr*)&address,
        sizeof(address)) < 0 || listen(sfd, 3) < 0
        || (connection = accept(sfd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
        catch("Error binding to server stream socket");
    
    char buffer[MAXSIZE];
    int n = read(connection, buffer, MAXSIZE);
    buffer[n] = '\0';

    shutdown(connection, SHUT_RDWR);
    close(connection);
    shutdown(sfd, SHUT_RDWR);
    close(sfd);

    catch("Get from stream socket error");
    
    return atoi(buffer);
}

send_stream_to_port(int port, int number)
{
    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return catch ();

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        catch("Error connecting to stream socket");

    char buffer[MAXSIZE];
    sprintf(buffer, "%d", number);
    send(sock, buffer, strlen(buffer), 0);

    shutdown(sock, SHUT_WR);
    close(sock);

    catch("Send to stream socket error");
}