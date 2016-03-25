#include "structure.h"
#include "Prim.h"
int main()
{
	List * graph = new List[N];
	char *inputfile = "karate.txt";
	ifstream fin; //输入文件 .join后结果
	int n = 0;
	double x, y, w;
	fin.open(inputfile);
	while (!fin.eof())
	{
		fin >> x >> y >> w;
		Pair a(y, w);
		Pair b(x, w);
		graph[int(x)].push_front(a);
		graph[int(y)].push_front(b);
		if (n <= x)
			n = x;
		if (n <= y)
			n = y;
	}
	fin.close();
	cout << "The total Node number is "
		<< n << endl;
	for (int i = 1; i <= n; i++)
		graph[i].print();

	Cell* Table = Prim(graph, n, 2);
	cout << "-----------------------\n";
	PrintTable(Table, n);
	system("pause");
	return 0;
}