#include <iostream>
using namespace std;
void revStr(char * str)
{
	int len = strlen(str);
	len--;
	int i = 0;
	while (len > i){
		char tmp = str[i];
		str[i] = str[len - 1];
		str[len] = tmp;
		//std::swap(str[i], str[len]); //��������������ַ������ǿ��Ե�
		i++, len--;
	}
}
int main()
{
	char * str = "Hello World, This is a test!";
	char arr[29];
	strcpy(arr, str);
	revStr(arr);
	cout << str << endl;
	cout << arr << endl;
	system("pause");
}