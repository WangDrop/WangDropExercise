/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2016年02月28日 星期日 13时08分56秒
 ************************************************************************/

#include <stdio.h>
#include "../helper.h"
int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc != 2)
        err_quit("Usage: TcpCli<IpAddress>");
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    Connect(sockfd, (SA*)&servaddr, sizeof(sockaddr));
    strcli(stdin, sockfd);
    exit(0);
}

void str_cli(FILE * fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    while(Fgets(sendline, MAXLINE, fp) != NULL){
        Writen(sockfd, sendline, strlen(sendline));
        if(Readline(sockfd, sendline, strlen(sendline)) == 0)
            err_quit("str_cli: server terminated permuturely");
        Fputs(sendline, stdout);
    }
}



