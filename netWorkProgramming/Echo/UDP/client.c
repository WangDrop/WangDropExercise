/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2016年02月28日 星期日 15时41分50秒
 ************************************************************************/

#include <stdio.h>
#include "./helper.h"
int main(int argc, char ** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc != 2){
        err_quit("Usage: udpcli <IPaddress>");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
}

int dg_cli(FILE * stream, int fd, const SA * addr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE];
    while((NULL != Fgets(sendline, MAXLINE, stdin))){
        Sendto(sockfd, sendline, strlen(sendline), 0, (SA*)(addr), sizeof(servlen));
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}
