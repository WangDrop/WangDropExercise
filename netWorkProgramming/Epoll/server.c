/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2016年03月05日 星期六 11时08分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100

//套接字的申明以及绑定
static int socketBind(const char * ip, int port);
//IO多路复用EPOLL
static void doEpoll(int listenfd);
//处理事务
static void handleEvents(int epollfd, struct epoll_event * events, int num, int listenfd, char * buf);
//处理接收到的链接
static void handleAccept(int epollfd, int sockfd);
//处理读以及写
static void doRead(int epollfd, int fd, char *buf);
static void doWrite(int epollfd, int fd, char * buf);
//添加事件
static void addEvent(int epollfd, int fd, int state);
//修改事件
static void reviseEvent(int epollfd, int fd, int state);
//删除事件
static void deleteEvent(int epollfd, int fd, int state);

static void modify_event(int epollfd, int fd, int state);


int main(int argc, char ** argv)
{
    int listenfd;
    listenfd = socketBind(IPADDRESS, PORT);
    listen(listenfd, LISTENQ);
    doEpoll(listenfd);
    return 0;
}


static int socketBind(const char * ip, int port)
{
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd = -1){
        perror("socket error !\n");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("bind error !\n");
        exit(1);
    }
    return listenfd;
}

static void doEpoll(int listenfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    int ret;
    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);
    //创建描述符
    epollfd = epoll_create(FDSIZE);
    //添加监听描述符事件
    addEvent(epollfd, listenfd, EPOLLIN);
    for(;;){
        //获得准备好了的描述符事件
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handleEvents(epollfd,events,ret,listenfd,buf);
    }
    close(epollfd);
}


static void handleEvents(int epollfd, struct epoll_event * events, int num, int listenfd, char * buf)
{
    int i, fd;
    //进行遍历
    for(i = 0; i < num; ++i){
        fd = events[i].data.fd;
        //判断不同的事务然后进行处理
        if((fd == listenfd)&&events[i].events & EPOLLIN)
            handleAccept(epollfd, listenfd);
        else if(events[i].events & EPOLLIN){ //读
            doRead(epollfd, fd, buf);
        }else if(events[i].events & EPOLLOUT){ //写
            doWrite(epollfd, fd, buf);
        }else{
            //do nothing;
        }
    }
}

static void handleAccept(int epollfd, int listenfd)
{
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
    if(clifd == -1){
        perror("accept Error!\n");
    }else{
        printf("accept a new client: %s : %d", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        addEvent(epollfd, clifd, EPOLLIN);
    }
}

static void doRead(int epollfd, int fd, char * buf)
{
    int n = read(fd, buf, MAXLINE);
    if(n == -1){
        perror("read error!\n");
        close(fd);
        deleteEvent(epollfd, fd, EPOLLIN);
    }else if(n == 0){
        fprintf(stderr, "client closed!\n");
    }else{
        printf("read the msg : %s \n", buf);
        //修改描述符的运行状态，从读改成写
        modify_event(epollfd, fd, EPOLLOUT);
    }
}

static void doWrite(int epollfd, int fd, char * buf)
{
    int n = write(fd, buf, strlen(buf));
    if(n == -1){
        perror("write error !\n");
        close(fd);
        deleteEvent(epollfd, fd, EPOLLOUT);
    }else{
        modify_event(epollfd, fd, EPOLLOUT);
    }
    memset(buf, 0, MAXLINE);
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

static void modify_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}


