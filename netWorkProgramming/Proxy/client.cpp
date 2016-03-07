/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月21日 星期四 21时19分53秒
 ************************************************************************/

#include<stdio.h>
#include"header.h"
#include"helper.h"
struct Receiver{
    struct sockaddr_in servAddr;
    int sockfd;
};

class Client{
private:
    struct sockaddr_in servAddr;
    int servPort;
    static int sockFd;
public:
    Client(string servIP, int port)
    :servPort(port)
    {
        bzero(&servAddr, sizeof(struct sockaddr_in));
        struct in_addr tmpAddr;
        tmpAddr.s_addr = htonl(INADDR_ANY);
        Myhelper::SetAddr(&servAddr, AF_INET, htons(port), tmpAddr);
        Myhelper::Inet_pton(AF_INET, servIP.c_str(), (void*)&servAddr.sin_addr.s_addr);
    }

    static void start(){
        sockFd = Myhelper::Socket(AF_INET, SOCK_DGRAM, 0);
        Receiver * receiver = new Receiver();
        receiver->sockfd = sockFd;
        receiver->servAddr = servAddr;
        pthread_t tid;
        pthread_create(&tid, NULL, recvMsg, (void*)(receiver));
    }

    static void * recvMsg(void * arg){
        pthread_detach(pthread_self());
        Receiver * recv = (Receiver *)arg;
        char line[MAXLINE + 1];
        while(true){
            int n = Myhelper::Recvfrom(sockFd, line, MAXLINE, 0, NULL, NULL);
            line[n] = 0;
            cout << endl << "Msg from proxy is : " << line;
            cout << "Msg to proxy: ";
        }
        return NULL;
    }

    static void * sendMsg(void * arg){
        Receiver * recv = (Receiver *)arg;
        char line[MAXLINE];
        while(true){
            cout << "Message to proxy: ";
            fgets(line, MAXLINE, stdin);
            if(strcmp(line, "exit") == 0)
                break;
            Myhelper::Sendto(sockFd, line, strlen(line), 0, (SA*)(&recv->servAddr), sizeof(recv->servAddr));
        }
    }

};

int main(int argc, char ** argv)
{
    if(argc != 3){
                    cout << "Usage: client [Proxy IP] [Proxy Port]" << endl;
                    exit(-1);
                
    }
            stringstream ss;
            ss << argv[2];
            int proxyPort;
            ss >> proxyPort;
            Client client(argv[1], proxyPort);
            client.start();
        
}

