#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <iostream>
#include <string>
#include <fstream>
#define N 10000
#define INFTY 2147483647
using namespace std;

class Pair {		//pair代表了与某个点相连的一条边的权重
private:			//，以及和这条变相连的另一个顶点是哪个
	double edge_weight;
	int adacent_vertex;
public:
	Pair(int, double);
	double weight() const;
	int vertex() const;
};


class Node { //代表了一个节点，其包含的信息有与其相连的
private:	 //某一条边的权重以及和这条边相连的另一个顶点。 
	Pair element;
	Node *next_node;
public:
	Node(Pair e, Node * = NULL);
	Pair retrieve() const;
	Node *next() const;
};


class List { //List中存放的是每个具体的节点，
private:	 //每个节点后面的链表代表的是与其相邻接的节点
	Node *list_head;
public:
	List();
	// Accessors
	bool empty() const;
	Pair front() const;
	Node *head() const;
	void push_front(Pair);
	Pair pop_front();
	void print();
};


class Cell { //cell代表的就是一个具体的生成树了
private:
	bool visited;
	double distance;
	int parent;
public:
	Cell(bool = false, double = INFTY, int = 0);
	bool isvisited() const;
	double get_distance() const;
	int get_parent() const;
};

#endif