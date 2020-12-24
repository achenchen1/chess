#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "80"

int main(int argc, char **argv) {
    struct addrinfo hints;
    struct addrinfo *res;
    int sockfd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    connect(sockfd, res->ai_addr, res->ai_addrlen);

    char* tester = malloc(5);
    strcpy(tester, "test");
    send(sockfd, tester, 5, 0);
    printf("sockfd %d", sockfd);

    recv(sockfd, tester, 5, 0);
    unsigned short local_port;
    struct sockaddr_in sin;
    int addrlen = sizeof(struct sockaddr_in);
    getsockname(sockfd, (struct sockaddr *)&sin, &addrlen); // read binding

    local_port = ntohs(sin.sin_port);
    printf("Answer: %s\n", tester);
    printf("Local port %hu\n", local_port);

    close(sockfd);
    free(tester);
    freeaddrinfo(res);
    return 0;
}
