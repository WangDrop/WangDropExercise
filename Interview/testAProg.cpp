#include <iostream>
using namespace std;

char* returnstr()
{
	char p[] = "hello";
	printf("%d\n", sizeof(p));
	printf("%d\n", strlen(p));
	return p;
}
int main()
{
	char* s = returnstr();
	printf("%s\n", s);
	system("pause");
	return 0;
}