/*************************************************************************
	> File Name: ShutDownServer.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年06月30日 星期四 18时02分05秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<event2/event.h>
#include<event2/util.h>
#include<string>
#include<sys/socket.h>
#include<unistd.h>
#include<memory.h>
using namespace std;

void cbFunc(evutil_socket_t sock, short what, void * arg)
{
    cout << "call back function is called !\n";
    struct event_base * base = (struct event_base *)arg;
    event_base_loopbreak(base);
}

void main_loop(struct event_base * base, evutil_socket_t watchdog_fd)
{
    cout << "The main loop function is called!\n"; 
    struct event * watchdog_event = event_new(base, watchdog_fd, EV_READ, cbFunc, base);//the last void * arg, now is base, so when get the event then can stop the dispatch;
    event_add(watchdog_event, 0);//blocking
    event_base_dispatch(base);
}
/*
 *This Server will block until the first conn coming, and then will ShutDown.
 */
int main()
{
    event_base * base = event_base_new();
    evutil_socket_t listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9527);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 10);

    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
    
    main_loop(base, listenfd);
}
