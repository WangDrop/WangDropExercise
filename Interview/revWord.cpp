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
		currLen += tmpP2 - tmpP1;
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

string reverseSten(const string & sentence)
{
	int len = sentence.len();
	if(len == 0) return "";
	string str = sentence;
	int curr = 0, pos = 0;
	while(cuur != len - 1){
		pos = str.find_first_of(curr, ' ');
		reverse(str.begin() + curr, str.begin() + pos);
		curr = pos + 1;
	}
	reverse(str.begin(), str.end());
	return str;
}

//上面的是使用c语言实现，下面的是使用c++的库函数实现的
string reverseSten(const string & sentence)
{
	int len = sentence.length();
	if (len == 0) return "";
	string str = sentence;
	int curr = 0, pos = 0;
	while (curr < len){
		pos = str.find_first_of(' ', curr); //注意这里的参数的位置
		if (pos == string::npos){
			reverse(str.begin() + curr, str.end());
			break;
		}
		reverse(str.begin() + curr, str.begin() + pos);
		curr = pos + 1;
	}
	reverse(str.begin(), str.end());
	return str;
}
