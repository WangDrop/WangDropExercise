/*************************************************************************
	> File Name: server.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年06月30日 星期四 21时01分37秒
 ************************************************************************/

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<event.h>
#include<string.h>
#define PORT 54321
#define BACKLOG 5
#define MEM_SIZE 1024


using namespace std;
struct sock_ev{
    struct event read_ev;
    struct event write_ev;
    char buffer[MEM_SIZE];
};

struct event_base * base = event_base_new();

void on_write(int sockfd, short event, void * arg)
{
    struct sock_ev * sockEv = (struct sock_ev *)arg;
    char * buffer = sockEv->buffer;
    send(sockfd, buffer, strlen(buffer), 0);
}


void on_read(int sockfd, short event, void * arg)
{
    int len = 0;
    struct sock_ev * sockEv = (struct sock_ev *)arg;
    char * buffer = sockEv->buffer;
    memset(buffer, 0, MEM_SIZE);
    len = recv(sockfd, buffer, MEM_SIZE, 0);
    if(len == 0){
        close(sockfd);
        return;
    }
    event_set(&sockEv->write_ev, sockfd, EV_WRITE, on_write, (void *)sockEv);
    event_base_set(base, &sockEv->write_ev);
    event_add(&sockEv->write_ev, NULL);//will block
}


void on_accept(int sockfd, short event, void * arg)
{
    struct sockaddr_in cliaddr;
    struct sock_ev sockEv;

    int clifd; 
    socklen_t clilen;
    clilen = sizeof(struct sockaddr_in);
    clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
    event_set(&sockEv.read_ev, clifd, EV_READ | EV_PERSIST, on_read, (void*)&sockEv);
    event_base_set(base, &sockEv.read_ev);
    event_add(&sockEv.read_ev, NULL);
}

int main()
{
    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(sockfd, BACKLOG);

    struct event listen_event;
    
    event_set(&listen_event, sockfd, EV_READ|EV_PERSIST, on_accept, NULL);

    event_base_set(base, & listen_event);

    event_add(&listen_event, NULL);

    event_base_dispatch(base);

    return 0;
}
