/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2016年03月03日 星期四 22时40分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <poll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXLINE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8787

static void handleConnection(int sockfd);

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    handleConnection(sockfd);
    return 0;
}

static void handleConnection(int sockfd)
{
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    int  maxfdp, stdineof;
    struct pollfd pfds[2];
    int n;
    //添加链接描述符
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;
    //添加标准输入描述符
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;
    for(;;){
        poll(pfds, 2, -1);
        if(pfds[0].revents & POLLIN){
            n = read(sockfd, recvline, MAXLINE);
            if(n == 0){
                fprintf(stdout, "The server is closeed!\n");
                close(sockfd);
            }
            write(STDOUT_FILENO, recvline, n);
        }

        if(pfds[1].revents & POLLIN){
            n = read(STDIN_FILENO, sendline, MAXLINE);
            if(n == 0){//now reach the EOF
                shutdown(sockfd, SHUT_WR);
                continue;
            }
            write(sockfd, sendline, n);
        }
    }
}
