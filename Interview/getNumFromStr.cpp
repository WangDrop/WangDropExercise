//使用long还是有可能造成溢出，实际上使用字符串最好
vector<long> findNum(const string & str){
	int len = str.length();
	int curr = 0;
	long num = 0;
	vector<long> res;
	while (curr < len){
		if (isdigit(str[curr])){
			num = num * 10 + (long)(str[curr] - '0');
			curr++;
			continue;
		}
		else{
			if (curr != 0){
				res.push_back(num);
				num = 0;
			}
			while (curr < len && !isdigit(str[curr])){
				curr++;
			}
		}
	}
	if (num != 0 || str[len - 1] == '0') //防止最后一个元素是0，或者是尾部字符是数字的情况
		res.push_back(num);
	return res;
}