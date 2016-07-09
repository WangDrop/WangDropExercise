#include "string.h"
#include "stdio.h"
#include "errno.h"
#include "signal.h"
#include "arpa/inet.h"
#include "sys/socket.h"

static const int PORT = 9995;
static const char *SERVADDR = "127.0.0.1";

int main() {
    struct sockaddr_in servaddr;
    int sockfd;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_aton(SERVADDR, &servaddr.sin_addr);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
        fprintf(stderr, "socket err!\n");
        return 1;
    }
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "connect err! %s\n", strerror(errno));
        return 1;
    }
    char recvBuffer[1024];
    char sendBuffer[1024];
    int n = 0;
    if ((n = recv(sockfd, recvBuffer, 1024, 0)) > 0) {
        recvBuffer[n] = '\0';
        printf("The msg from server is %s", recvBuffer);
    }
    return 0;
}
