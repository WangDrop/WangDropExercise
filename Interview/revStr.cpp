void revStr(char * str)
{
	int len = strlen(str);
	len--;
	int i = 0;
	while (len > i){
		char tmp = str[i];
		str[i] = str[len - 1];
		str[len] = tmp;
		i++, len--;
	}
}

//下面这种感觉稍微简介一点，好一点
void reverseStr(string & str)
{
	int end = str.length() - 1;
	for (int i = 0; i < end; ++i, --end){
		swap(str[i], str[end]);
	}
}