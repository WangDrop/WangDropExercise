#include "structure.h"
Cell* Prim(List * graph, int n, int start)  //����һ���ڽ����飬�Լ�����Ĵ�С��
{											//�Լ��ڽӾ������ʼ�㣬��һ����С������
	Cell* Table = new Cell[n + 1]; //n+1��Ŀ���ǽڵ��Ǵ�1��ʼ���ģ�����Ҫ�����һ��
	//Table[start]=Cell(false,0,0);//�����false�Ƿ񻻳�True���һ�㣿
	Table[start] = Cell(true, 0, 0);
	/* ʵ��prim�㷨*/
	int currMinNode, currParent = 0;
	double currMin;
	for (;;){
		currMin = INFTY; //ע�������������double����
		currMinNode = 0;
		currParent = 0;
		for (int i = 1; i <= n; ++i){
			if (Table[i].isvisited()){//�Ѿ������ʹ���
				Node * currNode = graph[i].head();
				while (currNode != NULL){ //�Ӹýڵ㿪ʼ��Ȼ����������е��ڽӵĽڵ�
					int tmpNode = currNode->retrieve().vertex();
					double tmpWeight = currNode->retrieve().weight();
					if (!Table[tmpNode].isvisited() && tmpWeight < currMin){
						currMin = tmpWeight;
						currMinNode = tmpNode;
						currParent = i;
					}
					currNode = currNode->next(); //ȡ��һ���ڽӵĽڵ�
				}
			}
			else
				continue;

		}
		Table[currMinNode] = Cell(true, currMin, currParent);//�ҵ���һ���ڵ㣬������ΪTrue
		if (currMinNode == 0) //������еĽڵ㶼�Ѿ�������ϵĻ�����ֹͣ��һ�ε�Ѱ��
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
