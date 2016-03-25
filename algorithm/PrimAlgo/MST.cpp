#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_NUM 100 //最大的节点个数
typedef struct VNode{
	struct VNode * next;
	int adjVec; //节点的编号
	double cost; //当前边的cost
}VNode;

typedef struct Head{ //链表的头结点
	int node; //头结点的信息
	struct VNode * first; //第一个节点的信息
}Head;

typedef struct MSTNode{
	int parent; //链接的前一个节点
	double cost; //权值
	int node; //节点的信息
}MSTNode;

Head graph[MAX_NUM];
MSTNode MST[MAX_NUM];
int totalNum; //图总结点个数
int arcNum; //图的边的总数

void getUserInput()
{
	char startC, endC;
	int start, end;
	double cost;
	int i;
	for (i = 0; i < MAX_NUM; ++i){
		graph[i].first = NULL;
		graph[i].node = -1;
	}
	memset(graph, 0, MAX_NUM * sizeof(Head));
	FILE * fin = fopen("graph.dat", "r"); //读取文件中的信息
	fscanf(fin, "%d %d", &totalNum, &arcNum);
	printf("请分别输入 开始节点 边权值 结束节点 的值： ");
	for (i = 0; i < arcNum * 2; ++i){//创建邻接表
		fflush(stdin);
		fscanf(fin, "%c %lf %c", &startC, &cost, &endC);
		start = startC - 65;
		end = endC - 65;
		if (graph[start].first == NULL){//在链表最前方插入
			graph[start].first = (VNode *)malloc(sizeof(VNode));
			graph[start].first->adjVec = end;
			graph[start].first->cost = cost;
			graph[start].first->next = NULL;
		}
		else{//已经存在点，在链表最前方插入
			VNode * tmp = graph[start].first;
			graph[start].first = (VNode *)malloc(sizeof(VNode));
			graph[start].first->adjVec = end;
			graph[start].first->cost = cost;
			graph[start].first->next = tmp;
		}
	}
	printf("读入图信息成功！\n");
	printf("该图对应的邻接表为：\n");
	for (i = 0; i < totalNum; ++i) //打印邻接表的信息
	{
		VNode * p = graph[i].first;
		printf("%c: ", i + 65);//打印出字母的值
		for (; p != NULL; p = p->next){
			printf("%d %.2f", p->adjVec, p->cost);
		}
		printf("\n");
	}
	printf("\n\n\n");
}


void findMST() //查找最小生成树
{
	printf("生成最小生成树中......\n\n");
	int currNum = 1; //当前MST中的节点个数
	int passed[MAX_NUM] = {0};
	passed[0] = 1;
	VNode * p;
	MSTNode newNode;
	newNode.cost = 100000.00;
	MST[0].parent = 0; //A顶点就是最开始的节点
	MST[0].cost = 0;
	MST[0].node = 0; //0代表节点'A'
	while (1){//使用Prim算法求最小生成树
		for (int i = 0; i < totalNum; i++){
			if (passed[i] != 0){
				for (p = graph[i].first; p != NULL; p = p->next){
					if (passed[p->adjVec] == 0){
						if (newNode.cost > p->cost){//比较cost'，只留下最小值
							newNode.parent = i;
							newNode.cost = p->cost;
							newNode.node = p->adjVec;
						}
					}
				}
			}
		}
		passed[newNode.node] = 1;
		MST[newNode.node] = newNode;
		newNode.cost = 100000.00;
		if (++currNum == totalNum)//表明所有节点都已经在生成树上了
			break; //搜索结束
	}
}

int main()
{
	getUserInput();
	findMST();
	int i = 0;
	printf("最小生成树上节点相邻的情况为：\n");
	for (; i < totalNum; ++i){//打印最小生成树情况
		if(MST[i].parent != MST[i].node)
			printf("边%d (%c, %c) 权值：%.2f\n", i, i + 65,  MST[i].parent + 65, MST[i].cost);
	}
	system("pause");
	return 0;
}
