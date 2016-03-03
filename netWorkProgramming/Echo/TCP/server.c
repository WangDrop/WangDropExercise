/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2016年02月28日 星期日 11时02分52秒
 ************************************************************************/

#include <stdio.h>
#include "../helper.h"
#define MAXLINE 1024
int main()
{   int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in ciaddr, servaddr;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    for(;;){
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, cliaddr, &clilen);
        if((child_pid = Fork()) == 0){//child process
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        Close(connfd); //parent process close the connfd
    }
}

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];
again:
    while((n = read(sockfd, buf, MAXLINE)) > 0)
        Writen(sockfd, buf, n);
    if(n < 0 && errno == EINTR)
        goto again;
    else if(n < 0)
        echo("str_echo: read error ! ");
}



