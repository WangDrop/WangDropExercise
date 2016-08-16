//自己实现(递归)
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

