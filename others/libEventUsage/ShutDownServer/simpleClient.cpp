/*************************************************************************
	> File Name: simpleClient.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年06月30日 星期四 19时23分04秒
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<cstdio>
#include<cstdlib>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
using namespace std;
int main()
{
    struct sockaddr_in servaddr;
    int clifd = 0;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(19527);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    clifd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == connect(clifd, (struct sockaddr *)&servaddr, sizeof(servaddr)));
        cout << "This means sth!\n";
    if(errno = ETIMEDOUT)
        cout << "time out !";

}
