#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <iostream>
#include <string>
#include <fstream>
#define N 10000
#define INFTY 2147483647
using namespace std;

class Pair {		//pair��������ĳ����������һ���ߵ�Ȩ��
private:			//���Լ�����������������һ���������ĸ�
	double edge_weight;
	int adacent_vertex;
public:
	Pair(int, double);
	double weight() const;
	int vertex() const;
};


class Node { //������һ���ڵ㣬���������Ϣ������������
private:	 //ĳһ���ߵ�Ȩ���Լ�����������������һ�����㡣 
	Pair element;
	Node *next_node;
public:
	Node(Pair e, Node * = NULL);
	Pair retrieve() const;
	Node *next() const;
};


class List { //List�д�ŵ���ÿ������Ľڵ㣬
private:	 //ÿ���ڵ����������������������ڽӵĽڵ�
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


class Cell { //cell����ľ���һ���������������
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