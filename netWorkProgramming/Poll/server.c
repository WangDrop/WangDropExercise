/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2016年03月03日 星期四 21时43分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#define IPADDR "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define OPEN_MAX 1000
#define INFTIM -1

static void handleConnection(struct pollfd * fds, int maxi);
static int sockBind(const char * ip, int port)
{
    struct sockaddr_in servaddr;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("Socket error !\n");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    if(bind(listenfd, (struct sockaddr*)(&servaddr), sizeof(servaddr)) == -1){
        perror("bind error !\n");
        exit(1);
    }
    return listenfd;
}

static doPoll(int listenfd)
{
    int connfd, sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    struct pollfd clientfds[OPEN_MAX];
    int i, maxi, nReady;
    //下面首先是监听描述符
    clientfds[0].fd = listenfd;
    clientfds[0].events = POLLIN;
    for(i = 1; i < OPEN_MAX; ++i){
        clientfds[i].fd = -1;
    }
    maxi = 0;
    for(;;){
        nReady = poll(clientfds, maxi+1, INFTIM); //无线超时
        if(nReady == -1){
            perror("poll Error !\n");
            exit(1);
        }
        if(clientfds[0].revents & POLLIN){
            cliaddrlen = sizeof(cliaddr);
            if((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen)) == -1){//这里说明一个客户端被暂时的关闭了
                if(errno == EINTR)
                    continue;
                else{
                    perror("pool error !\n");
                    exit(1);
                }
            }
            fprintf(stdout, "Accept a new client: %d:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
            //下面将新收到的链接添加到数组中
            for(i = 1; i < OPEN_MAX; i++){
                if(clientfds[i].fd < 0){
                    clientfds[i].fd = connfd;
                    break;
                }
            }
            if(i == OPEN_MAX){
                fprintf(stderr, "To many clients!\n");
                exit(1);
            }
            clientfds[i].events = POLLIN; //将描述符添加到描述符集合中
            //下面记录用户套接字的个数
            maxi = maxi>i?maxi:i;
            if(--nReady <= 0)
                continue;
        }
        handleConnection(clientfds, maxi);
    }
}

static void handleConnection(struct pollfd * connfds, int num)
{
    int i, n;
    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);
    for(i = 1; i <= num; ++i){
        if(connfds[i].fd < 0)
            continue;
        if(connfds[i].revents & POLLIN){
            printf("now get a msg from the client %d!\n", i);
            n = read(connfds[i].fd , buf, MAXLINE);
            if(n == 0){
                close(connfds[i].fd);
                connfds[i].fd = -1;
                continue;
            }
            write(STDOUT_FILENO, buf, n);
            write(connfds[i].fd, buf, MAXLINE); //同时的向客户端也发送这些消息
        }
    }
}

int main(int argc, char ** argv)
{
    int listenfd, connfd, sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    listenfd = sockBind(IPADDR, PORT);
    listen(listenfd, LISTENQ);
    doPoll(listenfd);
    return 0;
}
