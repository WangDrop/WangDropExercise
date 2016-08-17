#include <stdio.h>
#include <set>
#include <vector>
#define MAX  100000
#define VNUM  10+1                                             //这里没有ID为0的点,so id号范围1~10
using namespace std;

//注意这里邻接矩阵的形式是这样的，edge[i][i] = INT_MAX，不相连接的点之间的distance也为edge
int edge[VNUM][VNUM] = {/*输入的邻接矩阵*/ };
set<int> s;							                                      //标记某点是否加入Vnew
vector<int> res;


int primAlgo(int start)
{
	s.insert(start);
	int min = INT_MAX, minAdj = 0;
	while (s.size() < VNUM){
		int curr, minCurr;
		for (auto itor = s.begin(); itor != s.end(); ++itor){
			curr = *itor;
			for (int i = 0; i < VNUM; ++i){
				if (s.find(i) == s.end()){ //当前集合中是没有这个数的，那么可以
					if (edge[curr][i] < min){
						min = edge[curr][i];
						minCurr = curr;
						minAdj = i;
					}
				}
			}
		}
		s.insert(minAdj);
		res.push_back(minCurr); //使用前后两个节点来表示节点之间的一条直线
		res.push_back(minAdj);
	}
}