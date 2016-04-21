#include <iostream>
using namespace std;
int Strlen(char * s)
{
	int i = 0;
	while (s[i] != '\0'){
		i++;
	}
	return i;
}
int main()
{
	cout << "Test: " << Strlen("A Simple Test !\n") << endl;
	system("pause");
}