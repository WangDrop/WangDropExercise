//自己实现(递归)
//注意一下atoi的时候应该注意一下前导的括号以及正负号的问题等等
void itoa(int num, string & str)
{
	if (num / 10 == 0)
		str += num % 10 + '0';
	else{
		itoa(num / 10, str);
		str += num % 10 + '0';
	}
}

//借助与snprintf, 注意一下sprintf在打印出来的函数后面是默认的有一个'\0'的
void itoa(int num, char * buf, int len)
{
    assert(buf != NULL);
    snprintf(buf, len, "%d", num);
}

//自己实现
int atoi(string num)
{
	int res = 0;
	for (int i = 0; i < num.size(); ++i){
		res = res * 10 + num[i] - '0';
	}
	return res;
}

//借助库函数(好一点实际上可以加上参数的检查)
int atoi(string str)
{
	istringstream ss(str);
	int res;
	ss >> res;
	return res;
}



#include <iostream>
#include <functional>
#include <queue>
#include <vector>
using namespace std;
class Solution {
    priority_queue<int, vector<int>, less<int> > p; //使用less的是大顶堆
    priority_queue<int, vector<int>, greater<int> > q; //使用greater的是小顶堆
     
public:
    void Insert(int num){
        if(p.empty() || num <= p.top()) p.push(num);
        else q.push(num);
        if(p.size() == q.size() + 2) q.push(p.top()), p.pop();
        if(p.size() + 1 == q.size()) p.push(q.top()), q.pop();
    }
    double GetMedian(){ 
      return p.size() == q.size() ? (p.top() + q.top()) / 2.0 : p.top();
    }
};