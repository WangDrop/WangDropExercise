/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2016年03月05日 星期六 20时59分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAXSIZE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8787
#define FDSIZE 1024
#define EPOLLEVENTS 20

static void handleConnection(int sockfd);
static void handleEvents(int epollfd, struct epoll_event * events, int num, int sockfd, char * buf);
static void doRead(int epollfd, int fd, int sockfd, char * buf);
static void doWrite(int epollfd, int fd, int sockfd, char * buf);
static void addEvent(int epollfd, int fd, int state);
static void modifyEvent(int epollfd, int fd, int state);
static void deleteEvent(int epollfd, int fd, int state);

int main(int argc, char ** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = SERV_PORT;
    inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    //对链接进行处理
    handleConnection(sockfd);
    close(sockfd);
    return 0;
}

static void handleConnection(int sockfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    int ret;
    epollfd = epoll_create(FDSIZE);
    addEvent(epollfd, STDIN_FILENO, EPOLLIN);
    for(;;){ //不停的处理输入
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1); //注意epollevents大小不可以大于创建epoll时候的值的大小
        handleEvents(epollfd, events, ret, sockfd, buf);
    }
    close(epollfd);
}

static void handleEvents(int epollfd, struct epoll_event * events, int num, int sockfd, char * buf)
{
    int i, fd;
    for(i = 0; i < num; ++i){
        fd = events[i].data.fd;
        if(events[i].events & EPOLLIN){
            doRead(epollfd, fd, sockfd, buf);
        }else if(events[i].events & EPOLLOUT){
            doWrite(epollfd, fd, sockfd, buf);
        }
    }
}


static void doRead(int epollfd, int fd, int sockfd, char * buf)
{
    int n = read(fd, buf, MAXSIZE);
    if(n == -1){
        perror("read error !\n");
        close(fd);
    }else if(n == 0){
        fprintf(stdout, "server closed!\n");
        close(fd);
    }else{
        if(fd == STDIN_FILENO){
            addEvent(epollfd, sockfd, EPOLLOUT);
        }else{
            deleteEvent(epollfd, sockfd, EPOLLIN);
            addEvent(epollfd, STDOUT_FILENO, EPOLLOUT);
        }
    }
}


static void doWrite(int epollfd, int fd, int sockfd, char * buf)
{
    int n = write(fd, buf, strlen(buf));
    if(n == -1){
        perror("write error !\n");
        close(fd);
    }else{
        if(fd ==STDOUT_FILENO)
            deleteEvent(epollfd, fd, EPOLLOUT);
        else
            modifyEvent(epollfd, fd, EPOLLIN);
    }
    memset(buf, 0, MAXSIZE);
}

static void modifyEvent(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static void addEvent(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void deleteEvent(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

