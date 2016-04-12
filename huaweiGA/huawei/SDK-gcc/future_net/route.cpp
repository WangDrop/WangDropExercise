#include "route.h"
#include "lib_record.h"
#include "graph.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
	//Dij::Graph graph(topo, edge_num, demand);
	using namespace Dij;
	Graph graph(topo, edge_num, demand);
	//graph.printGraph();
	//char buf[2000];
    vector<int> vec(std::move(graph.getShortestPathDij()));
	//vector<int> vec(std::move(graph.getShortestPathDij()));
	//graph.shortestPathDijkstra(buf);
	cout << endl << endl << "The shortestPath is : " << endl;
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, "|"));
	int size = vec.size();
	for (int i = 0; i < size - 1; i++)
	    record_result(vec[i]);
	//cout << "Record over!\n";
}
