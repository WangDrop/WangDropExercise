#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_NUM 100 //���Ľڵ����
typedef struct VNode{
	struct VNode * next;
	int adjVec; //�ڵ�ı��
	double cost; //��ǰ�ߵ�cost
}VNode;

typedef struct Head{ //�����ͷ���
	int node; //ͷ������Ϣ
	struct VNode * first; //��һ���ڵ����Ϣ
}Head;

typedef struct MSTNode{
	int parent; //���ӵ�ǰһ���ڵ�
	double cost; //Ȩֵ
	int node; //�ڵ����Ϣ
}MSTNode;

Head graph[MAX_NUM];
MSTNode MST[MAX_NUM];
int totalNum; //ͼ�ܽ�����
int arcNum; //ͼ�ıߵ�����

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
	FILE * fin = fopen("graph.dat", "r"); //��ȡ�ļ��е���Ϣ
	fscanf(fin, "%d %d", &totalNum, &arcNum);
	printf("��ֱ����� ��ʼ�ڵ� ��Ȩֵ �����ڵ� ��ֵ�� ");
	for (i = 0; i < arcNum * 2; ++i){//�����ڽӱ�
		fflush(stdin);
		fscanf(fin, "%c %lf %c", &startC, &cost, &endC);
		start = startC - 65;
		end = endC - 65;
		if (graph[start].first == NULL){//��������ǰ������
			graph[start].first = (VNode *)malloc(sizeof(VNode));
			graph[start].first->adjVec = end;
			graph[start].first->cost = cost;
			graph[start].first->next = NULL;
		}
		else{//�Ѿ����ڵ㣬��������ǰ������
			VNode * tmp = graph[start].first;
			graph[start].first = (VNode *)malloc(sizeof(VNode));
			graph[start].first->adjVec = end;
			graph[start].first->cost = cost;
			graph[start].first->next = tmp;
		}
	}
	printf("����ͼ��Ϣ�ɹ���\n");
	printf("��ͼ��Ӧ���ڽӱ�Ϊ��\n");
	for (i = 0; i < totalNum; ++i) //��ӡ�ڽӱ����Ϣ
	{
		VNode * p = graph[i].first;
		printf("%c: ", i + 65);//��ӡ����ĸ��ֵ
		for (; p != NULL; p = p->next){
			printf("%d %.2f", p->adjVec, p->cost);
		}
		printf("\n");
	}
	printf("\n\n\n");
}


void findMST() //������С������
{
	printf("������С��������......\n\n");
	int currNum = 1; //��ǰMST�еĽڵ����
	int passed[MAX_NUM] = {0};
	passed[0] = 1;
	VNode * p;
	MSTNode newNode;
	newNode.cost = 100000.00;
	MST[0].parent = 0; //A��������ʼ�Ľڵ�
	MST[0].cost = 0;
	MST[0].node = 0; //0����ڵ�'A'
	while (1){//ʹ��Prim�㷨����С������
		for (int i = 0; i < totalNum; i++){
			if (passed[i] != 0){
				for (p = graph[i].first; p != NULL; p = p->next){
					if (passed[p->adjVec] == 0){
						if (newNode.cost > p->cost){//�Ƚ�cost'��ֻ������Сֵ
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
		if (++currNum == totalNum)//�������нڵ㶼�Ѿ�������������
			break; //��������
	}
}

int main()
{
	getUserInput();
	findMST();
	int i = 0;
	printf("��С�������Ͻڵ����ڵ����Ϊ��\n");
	for (; i < totalNum; ++i){//��ӡ��С���������
		if(MST[i].parent != MST[i].node)
			printf("��%d (%c, %c) Ȩֵ��%.2f\n", i, i + 65,  MST[i].parent + 65, MST[i].cost);
	}
	system("pause");
	return 0;
}
