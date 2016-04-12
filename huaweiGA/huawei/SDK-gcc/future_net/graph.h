/*************************************************************************
> File Name: graph.h
> Author:
> Mail:
> Created Time: 2016年03月07日 星期一 18时21分02秒
************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <queue>
#include <ctime>
#include <string.h>
#include <climits>
#include <algorithm>
#include <signal.h>
#include <unistd.h>
#include <iterator>
#include <random>
#include <unordered_set>
using namespace std;

const int MAX_VEX_NUM = 600;
const int MAX_SUB_VEX = 60;
const int LONGEST_PATH = 2048;


namespace Dij{ //namespace Dijstrka
	void timer(int sig);
	const int MAX_VEX_NUM = 600;
	struct Node{
		int arcNum;
		int cost;
		int nodeL;
		int nodeR;
		int nodeU;
		int nodeD;
		Node() :arcNum(-1), cost(10000), nodeL(-1), nodeR(-1), nodeU(-1), nodeD(-1){}
	};

	class Graph{
	public:
		Graph(){};
		Graph(char ** topo, int edge_num, char * demand);
		~Graph(){}
		
		void addEdge(int src_node, int dst_node, int arc_num, int cost);
		void printGraph();
		int dijkstra(int u, int v); //修改版本的dijkstra算法
		void getPath(int v, vector<int> & p);
		void getArcPath();
		int getNextNode(int u, int v);
		vector<int> getShortestPathDij();
		vector<int> getShortestPathDfs();
		void dfs(int u, int * mark, int cost, int domLeft, vector<int> & tmpPath);
	private:


		int largest;
		int edgeTotal;
		vector<int> dominator;
		vector<int> path;
		int dist[MAX_VEX_NUM];
		int pioneer[MAX_VEX_NUM];
		int mark[MAX_VEX_NUM];
		//queue<int> dijQueue; //dijkstra算法使用的队列
		int src, dst; //源节点以及目的节点
		int cost;

	};


}

//namespace GA{//generation algorithm
	//struct Node{
	//	int arcNum;
	//	int cost;
	//	int nodeL;
	//	int nodeR;
	//	int nodeU;
	//	int nodeD;
	//	Node() :arcNum(-1), cost(10000), nodeL(-1), nodeR(-1), nodeU(-1), nodeD(-1){}
	//};


	//const int SpSize = 80; //种群大小
	//const int crossSize = 20;
	//const int varSize = 10; //基因突变的概率
	//const int newCreate = crossSize + varSize;
	//const int G = 500; //迭代次数
	//const int ValidNum = 80; //有效基因的数量
	//const int totalGen = ValidNum + newCreate; //全部的320个gen
	//int comp(const void * left, const void * right);

	//const int MAX_WEIGHT = 10000;
	//const float invalidArcRatio[19] = { 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95, 1.00 };





	//void getGraph(char ** topo, int edge_num, char * demand);
	//void printGraph();

	//int myRand(int min, int max);
	//void seqVInit();

	//void addEdge(int u, int v, int arc, int cost);
	//void removeRowElem(int u, int v);
	//void removeColumn(int v);
	//void addColumn(int);
	//void insertV(int i, int v);
	//void dijkstra(int u, int v);
	//bool checkArc(int u, int v);//检测无效弧的数目
	//void getShortestPath(int v);
	//void geneGenerate(int u, int v, int index, int * mark, int * nodeNum);
	//void genCrossOver();
	//void genVar(); //基因变异
	//void genSelect();

	//void groupInit(int start, int end);
	//void groupInit2(int start, int end); //基因种群生成算法2

	//void GAStart();
//};
#   endif


