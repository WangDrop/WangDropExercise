#include <iostream>
#include <vector>
#include <cerrno>
#include <cstdlib>
#include <algorithm>
#include <sys/types.h>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string>
#include <iterator>
#include <cstdio>
#include <ctime>
#include <memory.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "helper.h"
using namespace std;
typedef struct sockaddr SA;
class Client{
private:
	struct timeval tm1, tm2;
	const static unsigned int SENDSIZE = 10 * 1024 * 1024; //10MB to send
	int port;
	int sockfd;
	int packetSend; //发包统计
	int packetLoss; //丢包统计
	struct sockaddr_in servAddr;
	int dataSize; //可以用来选择发送包的步进
	int sendNum; //发送包的计数
	int ackNum; //收到的ack计数
	int window; //窗口大小
	vector<unsigned char> data; //待发送的所有数据，数据量较小这样是可以的
	
	void init(){	
		ifstream in("get.txt");
		//ifstream<char>::iterator ibegin(in), iend;
		//data = vector<char> tmpVec(ibegin, iend); //使用流构造vector
		copy(istream_iterator<char>(in), istream_iterator<char>(), back_inserter(data));
		cout << "The size of send vec is " << data.size();
	}
public:
	Client(){} // default ctor
	Client(int _port, int _dataSize, int _window): //dataSize代表的是单个UDP数据报的大小
		port(_port), dataSize(_dataSize), window(_window), packetSend(0),
		packetLoss(0), sendNum(0), ackNum(0)
	{
		init();
		memset(&(tm1), 0, sizeof(struct timeval));
		memset(&(tm2), 0, sizeof(struct timeval));
		bzero(&servAddr, sizeof(servAddr));
		struct in_addr inTmp;
		inet_pton(AF_INET, "192.168.31.131", &inTmp); //中间的是我本机的ip地址
		Myhelper::SetAddr(&servAddr, AF_INET, port, inTmp);
		sockfd = Myhelper::Socket(AF_INET, SOCK_DGRAM, 0); //UDP使用SOCK_DGRAM
		int bufSize = 128 * 1024;	//设置socket缓冲区的大小
		Myhelper::SetSockOpt(sockfd, SOL_SOCKET, SO_RCVBUF, &bufSize, sizeof(bufSize));
		Myhelper::SetSockOpt(sockfd, SOL_SOCKET, SO_SNDBUF, &bufSize, sizeof(bufSize));
	}
	
	void start()
	{
		int packetTotal = SENDSIZE/dataSize; //要发送的包的总个数
		int packetSize = dataSize + 1; //包长的大小应该注意到开始的序号
		unsigned char sendBuf[dataSize+1];
		unsigned char recvBuf[4];
		unsigned char packetNum = 0; //用于记录包编号
		unsigned int byteSend = 0; //当前发送的总字节数
		int n = 0;
		bool timeFlag = true;
		while(packetSend < packetTotal){
			if(timeFlag){
				timeFlag = false;
				gettimeofday(&tm1, NULL);
			}
			//send packet
			for(int i = 0; i < window; ++i){
				sendBuf[0] = packetNum++; //包的序号从0开始
				memcpy(&sendBuf[1], &data[byteSend], dataSize);//vector保证数据存储在连续内存空间中，可用拷贝操作
				byteSend += dataSize;
				Myhelper::Sendto(sockfd, sendBuf, packetSize, 0, (SA*)&servAddr, sizeof(servAddr));
				packetSend++;
			}
		
			struct timeval tm;
			tm.tv_sec = 0;
			tm.tv_usec = 200000; //200ms timeout
			Myhelper::SetSockOpt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tm, sizeof(tm));
			n = Myhelper::Recvfrom(sockfd, recvBuf, 4, 0, NULL, NULL); //如果超时的话就会返回
			ackNum = recvBuf[0]; 
			if((int)ackNum != (packetSend%256)){ //防止溢出
				packetSend -= (packetSend + 256 - ackNum)%256; //得到要重发的包的开始点
				byteSend = packetSend * dataSize;
			}
			packetNum = ackNum; //当前应该发送的包的位置
		}
		gettimeofday(&tm2, NULL); //当所有的包发送完成之后再记录一次
	}
	
	void printData()const
	{
		for(int i = 0; i < 100; ++i){
			cout << data[i] << endl;
		}
	}
	
	void printTime() const //查看发送数据用掉的整体的时间
	{
		int sec = tm2.tv_sec - tm1.tv_sec;
		int msec = tm2.tv_usec - tm1.tv_usec;
		cout << "Time elapse: " << sec << "." << msec << "s" << endl;
	}
	
	int getElapsedTime() const //in micreSecs
	{
		if(tm1.tv_usec > tm2.tv_usec){
			return (tm2.tv_sec - tm1.tv_sec) * 1000000 - (tm1.tv_usec - tm2.tv_usec);
		}else{
			return (tm2.tv_sec - tm1.tv_sec) * 1000000 + (tm2.tv_usec - tm1.tv_usec);
		}
	}
	
	int getPacketLoss() const
	{
		int totalPacket = SENDSIZE/dataSize;
		cout << "Now send packetNum is : " << packetSend;
		return totalPacket - packetSend; //return packet loss；
	}
};

int main()
{
	Client c(9000, 32, 256);
	c.start();
	cout << "Time Use: " << c.getElapsedTime();
	cout << "Packet Loss: " << c.getPacketLoss();
}


