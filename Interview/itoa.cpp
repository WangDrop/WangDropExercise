#include <iostream>
#include <string>
using namespace std;
string itoa(int num, string & str)
{
	if (num / 10 == 0)
		str += num % 10 + '0';
	else{
		itoa(num/10, str);
		str += num % 10 + '0';
	}
	return str;
}

int atoi(string num)
{
	int res = 0;
	for (int i = 0; i < num.size(); ++i){
		res = res * 10 + num[i] - '0';
	}
	return res;
}

int main()
{
	string num;
	cout << "Test1 : " << itoa(553332323, num) << endl;
	cout << "Test2 : " << atoi("55665565") << endl;
	system("pause");
	return 0;
}

