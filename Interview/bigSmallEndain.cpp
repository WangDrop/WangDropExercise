#include <iostream>
using namespace std;
union test{
	char c[4];
	int num;
};
int main()
{
	test t;
	t.num = 0x01020304;
	if (t.c[0]){
		cout << "小端模式" << endl;
		printf("%x %x %x %x", t.c[0], t.c[1], t.c[2], t.c[3]);
	}
	else{
		cout << "大端模式" << endl;
		printf("%x %x %x %x", t.c[0], t.c[1], t.c[2], t.c[3]);
		cout << (int)t.c[0] << t.c[1] << t.c[2] << t.c[3];
	}
	system("pause");
	return 0;
}

