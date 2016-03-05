/*************************************************************************
	> File Name: proxy.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年01月20日 星期三 19时46分26秒
 ************************************************************************/

#include<iostream>
#include<algorithm> //for max
#include"helper.h"
#include"header.h"
using namespace std;
struct Receiver{
    struct sockaddr_in proxyAddr;
    struct sockaddr_in servAddr;
    struct sockaddr_in clientAddr;
    int proxyfd;
    int servfd;
};

class Proxy{
private:
    struct sockaddr_in proxyAddr;
    struct sockaddr_in servAddr;
    int proxyFd;
    int servFd;
    int proxyPort;
    int servPort;
public:
    Proxy(){} // default ctor
    Proxy(string _servIP, int _servPort, int _proxyPort)
    :servPort(_servPort), proxyPort(_proxyPort){
        bzero(&proxyAddr, sizeof(struct sockaddr_in));
        Myhelper::SetAddr(&proxyAddr, AF_INET, htons(proxyPort), htonl(INADDR_ANY));
        
        bzero(&servAddr, sizeof(struct sockaddr_in));
        Myhelper::SetAddr(&servAddr, AF_INET, htons(servPort), htonl(INADDR_ANY));
        Myhelper::Inet_pton(AF_INET, _servIP.c_str(), &servAddr.sin_addr.s_addr);
    } 

    int connServer()
    {
        servFd = Myhelper::Socket(AF_INET, SOCK_STREAM, 0);
        Myhelper::Connect(servFd, (SA*)(&servAddr), sizeof(struct sockaddr_in));
        return 0;
    }

    void * sendMsg(void * arg){
        char buf[MAXLINE];
        Receiver * receiver = (Receiver*)(arg);
        int n = 0;
        while((n = read(receiver->servFd, buf, MAXLINE)) > 0){
            buf[n] = 0
            Myhelper::Sendto(proxyFd, buf, n, 0, &receiver->clientAddr, sizeof(struct sockaddr_in));
        }
    }

    //recvmsg msg to clientAddr
    void * reavMsg(void * arg){
        pthread_detach(pthread_self()); //子线程中应该加入这一条
        Receiver * receiver = new Receiver();
        memcpy(receiver, &arg, sizeof(struct Receiver));
        static pthread_t tid = 0;
        char buf[MAXLINE+1];
        while(true){
            socklen_t clientLen = sizeof(receiver->clientAddr);
            n = Myhelper::Recvfrom(receiver->proxyFd, buf, MAXLINE, 0, (SA*)(&receiver->clientAddr), &clientLen);
            if(tid == 0){
                pthread_create(&tid, NULL, sendMsg, (void*)receiver);
            }
            buf[n] = 0;
            Myhelper::Write(receiver->servAddr, buf, n); 
        }   
    }

    void start()
    {
        connServer();
        proxyFd = Myhelper::Socket(AF_INET, SOCK_DGRAM, 0);
        Myhelper::Bind(proxyFd, (SA*)(&proxyAddr), sizeof(struct sockaddr_in));
        struct sockaddr_in clientAddr;
        char buf[MAXLINE + 1];
        fd_set rset;
        int maxfdp1;
        FD_ZERO(&rset);
        while(true){
            FD_SET(proxyFd, & rset);
            FD_SET(serverFd, & rset);
            maxfdpl = max(proxyFd, serverFd) + 1;
            Myhelper::Select(maxfdpl, &rset, NULL, NULL, NULL);
            if(FD_ISSET(proxyFd, & rset)){ //the client is readible
                socklen_t clientLen = sizeof(struct sockaddr_in);
                int n = Myhelper::Recvfrom(proxyFd, buf, MAXLINE, 0, (SA*)(clientAddr), &clientLen);
                buf[n] = 0;
                Myhelper::Write(serverFd, buf, n);
            }

            if(FD_ISSET(serverFd, & rset)){ //the server is readible
                int n = Read(serverFd, buf, MAXLINE);
                buf[n] = 0;
                sentto(proxyFd, buf, n, 0, (SA*)(clientAddr), sizeof(struct sockaddr_in));
            }
        }
    }
};

int main(int argc, char ** argv)
{
    if(argc != 3){
        cout << "Usage: proxy [Server IP] [Proxy Port]" << endl;
        exit(-1);
    }
    stringstream ss;
    ss << argv[2];
    int proxyPort;
    ss >> proxyPort;
    Proxy proxy(argv[1], 8000, proxyPort);
    proxy.start();
    return 0;
}
