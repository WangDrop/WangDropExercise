/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2016年03月07日 星期一 20时34分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define SIZE 10

typedef struct serverContext{
    int cliCnt; //客户端计数
    int clifds[SIZE]; //客户端的描述符
    fd_set  allfds; //句柄设计
    int maxfd;
}serverContext;

static serverContext * srvCtx = NULL;

static int createServerProc(const char * ip, int port)
{
    int fd;
    struct sockaddr_in servaddr;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        perror("Create Socket error !\n");
        exit(1);
    }
    int yes = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        return -1;
    int reuse = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reus, sizeof(int)) == -1)
        return -1;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_);
}

int main()
{
    int servfd;
    if(servInit() < 0){
        return -1;
    }
    srvfd = createServerProc(IPADDRESS, PORT);
    if(srvfd < 0){
        fprintf(stderr, "socket or bind failed !");
        goto err;
    }
    handleServerProc(servfd);
    return 0;

err:
    serverUninit();
    return -1;
}

int 
