

#include<sys/socket.h>//socket() bind()...
#include<stdio.h>//perror
#include<arpa/inet.h>//inet_pton()
#include<string.h>//bzero()
#include<stdlib.h>//exit()


#define port 7788
#define MAX_LINE 1000


void client_read(FILE *fp, int sockfd);

int
main(int argc, char **argv)
{
    int sockfd;
    char *str;
    struct sockaddr_in cliaddr;

    if(argc != 2)
    {
        printf("input right canshu");
        exit(1);
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
    }
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(port);
    if( inet_pton(AF_INET, argv[1], &cliaddr.sin_addr) !=1 )
    {
        printf("inet_pton error");
    }
    if((connect(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr))) == -1)
    {
        perror("connect error!!!");
        exit(0);
    }
}

