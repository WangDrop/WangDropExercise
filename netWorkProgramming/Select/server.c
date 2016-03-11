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
    servaddr.sin_port = htons(port);
    if(bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("Bindd error!\n");
        exit(-1);
    }
    listen(fd, LISTENQ);
    return fd;
}

static int acceptClient(int srvfd)
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen = sizeof(cliaddr);
    int clifd = -1;
ACCEPT:
    clifd = accept(srvfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
    if(clifd == -1){
        if(errno == EINTR)
            goto ACCEPT;
        else{
            fprintf(stderr, "acceptClient error: %s \n", strerror(errno));
            exit(1);
        }
    }

    fprintf(stdout, "accept new Client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
    //描述符添加到数组中
    int i = 0;
    for(int i = 0; i < SIZE; ++i){
        if(serverContext->clifds[i] < 0){
            serverContext->clifds = clifds;
            serverContext->cliCnt++;
            break;
        }
    }

    if(i == SIZE){
        fprintf(stderr, "To many clients !\n");
        exit(1);

    }
}


int handleClientMsg(int fd, char * buf)
{
    assert(buf);
    printf("recv buf is : %s \n", buf);
    write(fd, buf, strlen(buf) + 1);
    return 0;
}


static void recvClientMsg(fd_set * readFds)
{
    int i = 0, n = 0;
    int clifd;
    char buf[MAXLINE] = {0};
    for(i = 0; i < serverContext->cliCnt; ++i){
        clifd = serverContext->clifds[i];
        if(clifd < 0)
            continue;
        if(FD_ISSET(clifd, readFds)){
            n = read(clifd, buf, MAXLINE);
            if(n <= 0){
                FD_CLR(clifd, &serverContext->allfds);
                close(clifd);
                serverContext->clifds[i] = -1;
                continue;
            }
            handleClientMsg(clifd, buf);
        }
    }
}

static void handleClient(int srvfd)
{
    int clifd = -1;
    int retval = 0;
    fd_set * readfds = &serverContext->allfds;
    struct timeval tm;
    int i = 0;
    while(1){
        //注意，每次使用Select之前都应该设置文件描述符以及时间,因为事件发生之后，这些信息又都会被修改了
        FD_ZERO(readfds);
        FD_SET(srvfd, readFds);
        serverContext->maxfd = srvfd;

        tv.tv_sec = 30;
        tv_tv_usec = 0;
        for(i = 0; i < serverContext->cliCnt; i++){
            clifd = serverContext->clifds[i];
            FD_SET(clifd, readFds);
            serverContext->maxfd = (clifd > serverContext->maxfd ? clifd : serverContext->maxfd);
        }
        retval = select(serverContext->maxfd + 1, readFds,NULL, NULL, NULL, &tv);
        if(retval == -1){
            fprintf(stderr, "Select error %s .\n", strerror(errno));
            exit(0);
        }

        if(retval == 0){
            fprintf(stdout, "select is tomeout.\n ");
            continue;
        }

        if(FD_ISSET(servfd, readFds)){
            acceptClient(srvfd);
        }else{
            recvClientMsg(readFds);
        }
    }
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
