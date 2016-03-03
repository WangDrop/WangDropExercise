#include <iostream>
#include <string>
#include <vector>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <set>
#include <cstdio>
#include "helper.h"

using namespace std;
typedef struct sockaddr SA;
const unsigned int BUFSIZE = 128 * 1024;
class Server{
private:
	int window; 
	int port;
	int sockfd;
	struct sockaddr_in servAddr;
	struct sockaddr_in cliAddr;
	vector<char> recv;
public:
	Server(){}; //default constructor
	Server(int _port, int _window)
	: port(_port), window(_window)
	{
		bzero(&servAddr, sizeof(servAddr));
        struct in_addr tmpAddr;
        tmpAddr.s_addr = htonl(INADDR_ANY);
		Myhelper::SetAddr(&servAddr,  AF_INET, htons(port), tmpAddr);
		sockfd = Myhelper::Socket(AF_INET, SOCK_DGRAM, 0);
		Myhelper::SetSockOpt(sockfd, SOL_SOCKET, SO_RCVBUF, &BUFSIZE, sizeof(unsigned char));
		Myhelper::SetSockOpt(sockfd, SOL_SOCKET, SO_SNDBUF, &BUFSIZE, sizeof(unsigned char));
		Myhelper::Bind(sockfd, (SA*)(&servAddr), sizeof(servAddr));
	}


	void start(){
		int n;
		socklen_t len;
		unsigned char msg[20000];
		unsigned char ackBuf[1];
		unsigned char except = 0;
        set<unsigned char> tmpSet; //由于UDP不保证能够按照序号正确传输，所以这里使用set相当于使用了一次排序
		while(true){
			len = sizeof(cliAddr); 
			for(int i = 0; i < window; ++i){
				bzero(msg, sizeof(msg));
				n = Myhelper::Recvfrom(sockfd, msg, 20000, 0, (SA*)&cliAddr, &len);
			}
			tmpSet.insert(msg[0]); 
		}
		for(set<unsigned char>::iterator it = tmpSet.begin(); it != tmpSet.end(); ++it){
			/*if(*it == except){
				except++;
				ackBuf[0] = except;
				Myhelper::Sendto(sockfd, ackBuf, 1, 0, (SA*)&cliAddr, len);
			}else{
				ackBuf[0] = except;
				Myhelper::Sendto(sockfd, ackBuf, 1, 0, (SA*)&cliAddr, len);
				cout << "Client should retransmit!\n";
				break;
			}*/
			while(*it == except){ //丢弃一部分，然后窗口向前滑动n个
				except++;
				ackBuf[0] = except;
			}
			Myhelper::Sendto(sockfd, ackBuf, 1, 0, (SA*)&cliAddr, len);
		}
	}
};

int main()
{
	Server server(9000, 256);
	server.start();
}

