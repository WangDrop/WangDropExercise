#include <iostream>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <fcntl.h>
using namespace std;

class Myhelper{
public:
    static int bzero(void * ptr, size_t n)
    {
            memset(ptr, 0, n);

    }

	static void perrExit(const string & str){
		perror(str.c_str());
		exit(1);
	}

	static void SetAddr(sockaddr_in * socket, short family, unsigned short port, struct in_addr addr){
		socket->sin_family = family;
		socket->sin_port = port;
		socket->sin_addr = addr;
	}

	static int Socket(short family, int type, int protocal){
		int n ;
		if((n = socket(family, type, protocal)) < 0)
			perrExit("Socket Error!\n");
		return n;
	}

	static void SetSockOpt(int s, int level, int optname, const void * optval,socklen_t optlen){
		if(setsockopt(s, level, optname, optval, optlen) != 0)
			perrExit("SetSockOpt error!\n");
	}

	static void Bind(int fd, struct sockaddr * sa, socklen_t salen){
		if(bind(fd, sa, salen) < 0)
			perrExit("Bind error !\n");
	}
	
	static void Listen(int sockfd, int backlog){
		if(listen(sockfd, backlog) != 0)
			perrExit("Listen error!\n");
	}

	static int Recvfrom(int s, void *buf, int len, unsigned int flags, struct sockaddr *from,socklen_t *fromlen){
		int n = 0;
		if((n = recvfrom(s, buf, len, flags, from, fromlen)) < 0){
			perrExit("Recvfrom error !\n");
		}
		return n;
	}

	static int Sendto(int s, const void * msg, int len, unsigned int flags, const struct sockaddr * to, int tolen){
		if(sendto(s, msg, len, flags, to, tolen) < 0)
			perrExit("Sendto Error!\n");
	}

    static int Select(int maxfdpl, fd_set * readset, fd_set * writeset, fd_set * exceptset,struct timeval * timeout ){
        if(select(maxfdpl, readset, writeset, exceptset, timeout) < 0)
        perrExit("select Error!\n");
    }

    static int Inet_pton(int af, const char * src, void *dst){
        if(inet_pton(af, src, dst) != 1)
            perrExit("inet_pton error!\n");
    }

    static int Connect(int sockfd, struct sockaddr * serv_addr, int addrlen)
    {
        if(connect(sockfd, serv_addr, addrlen) < 0)
            perrExit("Connetc error!");
    }
    
    static int Accept(int sockfd, struct sockaddr * sa, socklen_t * addrlen)
    {
		if(accept(sockfd, sa, addrlen) < 0){
			perrExit("Accept error!\n");
		}
	}
    
    static int Read(int sockfd, void * buf, size_t len){
		if(read(sockfd, buf, len) < 0)
			perrExit("Read Error!\n");
	}
	
	static int Write(int sockfd, void * buf, int nByte){
		if(write(sockfd, buf, nByte) < 0)
			perrExit("Write error!\n");
	}

    static struct hostent * Gethostbyname(const char * name)
    {
        struct hostent * ent;
        if((ent = gethostbyname(name)) == NULL){
            perrExit("Gethostbyname Error !\n");
        }
        return ent;
    }
};



