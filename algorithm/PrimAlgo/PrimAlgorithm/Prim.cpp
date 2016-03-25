#include "structure.h"
Cell* Prim(List * graph, int n, int start)  //传入一个邻接数组，以及数组的大小，
{											//以及邻接矩阵的起始点，求一个最小生成树
	Cell* Table = new Cell[n + 1]; //n+1的目的是节点是从1开始数的，所以要多添加一个
	//Table[start]=Cell(false,0,0);//这里的false是否换成True会好一点？
	Table[start] = Cell(true, 0, 0);
	/* 实现prim算法*/
	int currMinNode, currParent = 0;
	double currMin;
	for (;;){
		currMin = INFTY; //注意这个的类型是double类型
		currMinNode = 0;
		currParent = 0;
		for (int i = 1; i <= n; ++i){
			if (Table[i].isvisited()){//已经被访问过了
				Node * currNode = graph[i].head();
				while (currNode != NULL){ //从该节点开始，然后访问其所有的邻接的节点
					int tmpNode = currNode->retrieve().vertex();
					double tmpWeight = currNode->retrieve().weight();
					if (!Table[tmpNode].isvisited() && tmpWeight < currMin){
						currMin = tmpWeight;
						currMinNode = tmpNode;
						currParent = i;
					}
					currNode = currNode->next(); //取下一个邻接的节点
				}
			}
			else
				continue;

		}
		Table[currMinNode] = Cell(true, currMin, currParent);//找到下一个节点，将其置为True
		if (currMinNode == 0) //如果所有的节点都已经遍历完毕的话，就停止下一次的寻找
			break;

	}
	return Table;
}

void PrintTable(Cell* Table, int n)
{
	for (int i = 1; i <= n; i++)
		cout << Table[i].isvisited() << " " <<
		Table[i].get_distance() << " " <<
		Table[i].get_parent() << endl;
}
