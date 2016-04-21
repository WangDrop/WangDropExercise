//将字符串以单词为单位进行反转
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
char * revStr(char * str)
{
	char * res = new char[strlen(str) + 1];
	vector<char * > pos;
	pos.clear();
	char * p = str;
	int len = strlen(str);
	while ((p = strchr(p, ' ')) != NULL){
		pos.push_back(p);
		p++;
	}
	pos.push_back(str + len);
	int currLen = 0;
	while (pos.size() >= 2){
		char * tmpP2 = pos[pos.size() - 1];
		char * tmpP1 = pos[pos.size() - 2];
		strncpy(res + currLen, tmpP1 + 1, tmpP2 - tmpP1 - 1);
		currLen += tmpP2 - tmpP1; //加上一个空格
		res[currLen - 1] = ' ';
		pos.pop_back();
	}
	strncpy(res + currLen, str, pos[0] - str );
	res[len] = '\0';
	return res;
}

char * revStr2(char * str)
{
	int len = strlen(str);
	int currlen = 0;
	char * res = new char[len + 1];
	char * p1 = str;
	char * p2 = strchr(str, ' ');
	while (p2 != NULL){
		strncpy(res + currlen, p1, p2 - p1);
		reverse(res + currlen, res + (p2 - p1) - 1);
		currlen += p2 - p1;
		res[currlen++] = ' ';
		p1 = p2 + 1;
		p2 = strchr(p1, ' ');
	}
	strncpy(res + currlen, p1, res + len - p1);
	reverse(res + currlen, res + len - 1);
	reverse(res, res + len - 1);
	return res;
}

void reverse(char * start, char * end)
{
	cout << *start << " " << *end;
	while (end > start){
		swap(*start, *end);
		start++, end--;
	}
}

int main()
{
	char * str = "Hello World, This is a test!";
	char * res = revStr2(str);
	cout << str << endl;
	cout << res << endl;
	system("pause");
}