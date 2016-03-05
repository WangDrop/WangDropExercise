/*************************************************************************
	> File Name: server.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年01月20日 星期三 21时56分08秒
 ************************************************************************/

#include "header.h"
#include "helper.h"
class Server{
private:
    struct sockaddr_in serverAddr;
    int serverPort;
    int listenFd;

public:
    static vector<int> clients;
    Server(){}; // default ctor
    Server(int port){
        serverPort = port;
        Myhelper::SetAddr(&serverAddr, AF_INET, htons(serverPort), htonl(INADDR_ANY));
    }

    static void response(int connfd){
        char buf[MAXLINE];
        int n;
        while((n = read(connfd, buf, MAXLINE)) > 0){

            buf[n] = 0;
            for(int i = 0; i < clients.size(); ++i){
                if(connfd != clients[i]){
                    Myhelper::Write(clients[i], buf, MAXLINE);
                }
            }
        }
    }

    void * doit(void *){
        long connfd = (long)((int *)arg);
        pthread_detach(pthread_self());
        response(connfd);
        close(connfd);
        return NULL;
    }
    
    void start(){
        listenFd = Myhelper::Socket(AF_INET, SOCK_STREAM, 0);
        int onoptval = 1;
        Myhelper::SetSockOpt(listenFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&onoptval, sizeof(int));
        Myhelper::Bind(listenFd, (SA*)&serverAddr, sizeof(serverAddr));
        pthread_t tid;
        socklen_t clilen = sizeof(clientAddr);
        struct sockaddr_in * clientAddr;
        Myhelper::Listen(listenFd, 5);
        clientAddr = (sockaddr_in *)malloc(sizeof(struct sockaddr_in));
        while(true){
            clilen = sizeof(clientAddr);
            int connfd = Myhelper::Accept(listenFd, (SA*)(&clientAddr), &clilen);
            clients.push_back(connfd);
            cout << "Now the number of clients is : " << clients.size() << endl;
            pthread_create(&tid, NULL, &doit, (void*)connfd);
        }
    }
};

vector<int> Server::clients;
int main()
{
    int serverPort = 8000;
    Server server(serverPort);
    server.start();
}
