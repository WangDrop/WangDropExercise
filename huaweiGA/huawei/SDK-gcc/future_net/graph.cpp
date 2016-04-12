#include "graph.h"

Dij::Node graph[MAX_VEX_NUM][MAX_VEX_NUM];
Dij::Node graphHeadH[MAX_VEX_NUM];
Dij::Node graphHeadV[MAX_VEX_NUM];
bool depthMark[100][100]; //递归应该不会超过100层

int graphHeadLength[MAX_VEX_NUM] = {0};

bool timeOver = false;
void Dij::timer(int sig)
{
    timeOver = true;
}

Dij::Graph::Graph(char ** topo, int edge_num, char * demand)
	:cost(INT_MAX), edgeTotal(edge_num), largest(0)
{
	dominator.reserve(50);
	path.reserve(MAX_VEX_NUM);
	char * p, *p1, *p2, *p3;
	srand(time(NULL));
	p = demand;
	p1 = strchr(demand, ',');
	p2 = strchr(p1 + 1, ',');
	*p1 = *p2 = '\0';
	src = atoi(p);
	dst = atoi(p1 + 1);
	p = p2 + 1; //start to find the punct '|'

	while (p != NULL){
		//cout << "The str now is " << p;
		char * tmpP = strchr(p, '|');
		if (tmpP != NULL){
			*tmpP = '\0';
			dominator.push_back(atoi(p));
			p = tmpP + 1;
		}
		else
			break;
	}
	dominator.push_back(atoi(p));

	int arc_num;
	int src_node;
	int dst_node;
	int cost;
	for (int i = 0; i < edgeTotal; ++i){
		p = topo[i];
		p1 = strchr(p, ',');
		p2 = strchr(p1 + 1, ',');
		p3 = strchr(p2 + 1, ',');
		*p1 = *p2 = *p3 = '\0';

		arc_num = atoi(p);
		src_node = atoi(p1 + 1);
		dst_node = atoi(p2 + 1);
		cost = atoi(p3 + 1);
		addEdge(src_node, dst_node, arc_num, cost);
	}
}

void Dij::Graph::addEdge(int u, int v, int arc, int cost)
{
	int k;
	if (u > largest) largest = u;
	if (v > largest) largest = v;
	if (graphHeadH[u].nodeR == -1){//起点为U的第一条边,一定需要添加到图中
        graphHeadLength[u]++;
		graphHeadH[u].nodeL = graphHeadH[u].nodeR = v;
		graph[u][v].cost = cost;
		graph[u][v].arcNum = arc;
		if (graphHeadV[v].nodeD == -1){//终点为V的第一条边
			graphHeadV[v].nodeU = graphHeadV[v].nodeD = u;
		}
		else{
			k = graphHeadV[v].nodeU; //最近一次输入的以v为终点的边的起点
			graph[k][v].nodeD = u;
			graph[u][v].nodeU = k;
			graphHeadV[v].nodeU = u;
		}
	}
	else{ //不是起点为u的第一条边
		k = graphHeadH[u].nodeL;
		if (graph[u][v].nodeL != -1 || graph[u][v].nodeR != -1){
			if (graph[u][v].cost > cost){
				graph[u][v].cost = cost;
				graph[u][v].arcNum = arc;
			}
		}
		else{
            graphHeadLength[u]++;
			graph[u][k].nodeR = v;
			graph[u][v].nodeL = k;
			graph[u][v].cost = cost;
			graph[u][v].arcNum = arc;
			graphHeadH[u].nodeL = v;
		}
		if (graphHeadV[v].nodeD == -1){//以v为终点的第一边
			graphHeadV[v].nodeD = graphHeadV[v].nodeU = u;
		}
		else{//不是以v为终点的第一条边
			k = graphHeadV[v].nodeU;
			graph[k][v].nodeD = u;
			graph[u][v].nodeU = k; //这时候还没设置nodeD，nodeD可以作为哨兵，即-1
			graphHeadV[v].nodeU = u;
		}
	}
}

void Dij::Graph::printGraph()
{
	for (int i = 0; i <= largest; ++i){
		int j = graphHeadH[i].nodeR;
		while (j != -1){
			cout << graph[i][j].arcNum << " " << i << " " << j << " " << graph[i][j].cost << endl;
			j = graph[i][j].nodeR;
		}
		cout << endl;
	}
}

//get dijkstra
int Dij::Graph::dijkstra(int s, int d)
{
	int u, v;
	queue<int> dijQueue;
	mark[s] = mark[d] = 0;
	for (int i = 0; i <= largest; ++i){
		dist[i] = INT_MAX;
		pioneer[i] = i;
	}
	dist[s] = 0;
	pioneer[d] = d;
	dijQueue.push(s);
	while (!dijQueue.empty()){
		u = dijQueue.front();
		dijQueue.pop();
		if (mark[u] == 1)
			continue;
		if (u == d)
			return dist[d];
		v = graphHeadH[u].nodeR;
		while (v != -1){
            if (mark[v] != 1 && dist[v] > dist[u] + graph[u][v].cost){
				dist[v] = dist[u] + graph[u][v].cost;
                pioneer[v] = u;
				dijQueue.push(v);
			}
			v = graph[u][v].nodeR;
		}
	}
	mark[s] = mark[d] = 1;
	return dist[d];
}

int Dij::Graph::getNextNode(int u, int v)
{
    if(graphHeadLength[u] == 0)
        return -1;
	int rd = 1 + rand() % graphHeadLength[u];
	int next = v;
	while (rd != 0){
		rd--;
		next = graph[u][next].nodeR;
		if (next == -1)
			next = v;
	}
	if (next == v)
		return -1;
	return next;
}

vector<int> Dij::Graph::getShortestPathDij()
{
	std::random_device rd;
	std::mt19937 g(rd());
	int domSize = dominator.size();
	vector<int> tmpPath;
	tmpPath.reserve(MAX_VEX_NUM);
	int tmpCost;
	int tmp;
    int count = 0;
    timeOver = false;
    signal(SIGALRM, timer);
    alarm(1);
    getShortestPathDfs();

   // cout << "####" << cost  << endl;
    if(!timeOver && cost != INT_MAX)
        return path;
    timeOver = false;
    alarm(10);
    do{
		shuffle(dominator.begin(), dominator.end(), g);
		memset(mark, 0, sizeof(int) * (largest + 1));
		tmpPath.clear();
		tmpCost = 0;
        tmp = 0;
		for (int i = 0; i < domSize; ++i)
			mark[dominator[i]] = 1;
		mark[src] = mark[dst] = 1;
		tmp = dijkstra(src, dominator[0]);
		if (tmp == INT_MAX) continue;
		tmpCost += tmp;
        getPath(dominator[0], tmpPath);
		for (int i = 1; i < domSize; ++i){
			tmp = dijkstra(dominator[i-1],dominator[i]);
            if (tmp == INT_MAX) break;
			tmpCost += tmp;
			getPath(dominator[i], tmpPath);
        }
		if (tmp == INT_MAX) continue;
		tmp = dijkstra(dominator[domSize - 1], dst);
		if (tmp == INT_MAX) continue;
		tmpCost += tmp;
		getPath(dst, tmpPath);
        //cout << tmpCost << " " << cost << endl;
		if (tmpCost < cost){
			cost = tmpCost;
			path = tmpPath;
			cout << "Cost: " << cost << endl;
			copy(path.begin(), path.end(), ostream_iterator<int>(cout, "->"));
			cout << endl;
            getArcPath();
            if(++count == 10)
                return path;
		}
	} while (!timeOver);
    return path;
}


vector<int> Dij::Graph::getShortestPathDfs()
{
	int size = dominator.size();
	memset(mark, 0, sizeof(int) * (largest + 1));
	for (int i = 0; i < size; ++i){
		mark[dominator[i]] = 1;
	}
	int pathMark[MAX_VEX_NUM];
	int tmpCost = 0;
	vector<int> tmpPath;
	tmpPath.reserve(MAX_VEX_NUM);
	int domLeft = dominator.size();
	memset(pathMark, 0, sizeof(int) * (largest + 1));
	tmpPath.push_back(src);
	pathMark[src] = 1;
    while(!timeOver){
        dfs(src, pathMark, tmpCost, domLeft, tmpPath);
    }
	  
	getArcPath();
	return path;
}

void Dij::Graph::dfs(int u, int * pathMark, int tmpCost, int domLeft, vector<int> & tmpPath)
{
	for (int v = graphHeadH[u].nodeR; v != -1 && !timeOver; v = graph[u][v].nodeR/*getNextNode(u, v)*/){
		if (pathMark[v] == 0){
			if (v == dst){
				if (domLeft == 0 && tmpCost + graph[u][v].cost < cost){
					path = tmpPath;
					path.push_back(dst);
                    cost = tmpCost + graph[u][v].cost;
				    //cout << "MinCost:  " << cost <<  " " << INT_MAX << endl;
					//copy(path.begin(), path.end(), ostream_iterator<int>(cout, "->"));
					//cout << endl;
				}
				continue;
			}
			pathMark[v] = 1;
			tmpPath.push_back(v);
			tmpCost += graph[u][v].cost;
			if (mark[v] == 1)
				domLeft--;
			if (tmpCost < cost && !timeOver)
				dfs(v, pathMark, tmpCost, domLeft, tmpPath);
			pathMark[v] = 0;
			tmpPath.pop_back();
			tmpCost -= graph[u][v].cost;
			if (mark[v] == 1)// isDom
				domLeft++;
        }
	}
}


void Dij::Graph::getPath(int v, vector<int> & p)
{
	if (pioneer[v] == v){
		if (p.size() == 0)
			p.push_back(v);
		mark[v] = 1;
	}
	else{
		getPath(pioneer[v], p);
		p.push_back(v);
		mark[v] = 1;
	}
}

void Dij::Graph::getArcPath()
{
	int size = path.size();
    if(size == 0) return;
	int u = path[0], v = u;
	for (int i = 0; i < size - 1; ++i){
		u = v;
		v = path[i+1];
		path[i] = graph[u][v].arcNum;
	}
	//copy(path.begin(), path.end() - 1, ostream_iterator<int>(cout, "->"));
	//cout << endl;
}
