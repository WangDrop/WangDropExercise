#include "function.h"
char fileContent[MAX_LINE][MAX_LINE_LEN];
struct Varible allVarible[4096];
int varCount = 0;
int lineCount = 0;

/*
**func: 读取文件内容到数组中
**arg:	fileName: 文件名
**
*/
int getContent(const char *fileName)
{
	FILE * fp;
	if ((fp = fopen(fileName, "r")) == NULL){
		//printf("Sorry, can't open target file!\n");
		exit(0);
	}
	else{
		while (feof(fp) == 0){
			if (NULL == fgets(fileContent[lineCount], MAX_LINE_LEN, fp)){
				//printf("reach the file end!");
				return 0;
			}
			else{
				//printf("The line Count is %d.", lineCount);
				lineCount++;
			}
		}
	}
	return 0;
}


/*
**func: 处理一行的内容
**arg:	line:行内容 
**
*/
int getVarValue(const char * line)  //根据本行的内容来判断，是声明还是计算
{									//（注意，由于print语法较为简单，所以规定print语句也在声明函数中进行处理）
	if (line == NULL){
		//printf("Error! The Line is Empty!\n");
	}
	if (strstr(line, "int") == NULL && 
		strstr(line, "double") == NULL && 
		strstr(line, "print") == NULL){	//改行是计算，非声明
		processTheInput(line);
		if (getVarCalculate(line) == DEVIDE_ERROR){
			printf("divided by ZERO\n");
			return DEVIDE_ERROR; //出现除0错误的时候直接返回，不继续进行下面的
		}
	}
	else{								//改行是声明
		getVarDeclare(line);
	}
	return 0;
}


/*
**func: 预处理一行的内容，将*-这种形式，变成*(0-)这种形式
**arg:	line: 一行内容
**
*/
void processTheInput(const char * line)
{
	char * p = line;
	char * end = NULL;
	int lineLen = strlen(line);
	while ((p = strstr(line, "+-")) != NULL || (p = strstr(line, "--")) != NULL ||
		(p = strstr(line, "*-")) != NULL || (p = strstr(line, "/-")) != NULL){
		lineLen = strlen(line) - 1;
		end = line + lineLen;
		end[3] = '\0';
		end[0] = ' ';
		memcpy(p + 2, p + 1, end - p); //将内容向后移动
		p[1] = '(';
		p[2] = '0';
		p += 3;
		if (p[1] == '('){//如果符号后面本来就有括号的话
			while (*p != ')'){//指针后移，尝试将括号也括进来
				p++;
			}
		}
		strcpy(p + 2, p + 1);
		p[1] = ')';
	}
	return; //不需要进行预处理

}



/*
**func: 用于得到声明的所有变量
**arg:	line: 一行内容
**
*/
int getVarDeclare(const char * line)
{
	char * p = line;
	int varLen = 0;
	char valStr[MAX_CONST_LEN]; // 保存print内可能会出现的数字
	if ((p = strstr(line, "double")) != NULL){//该行是double的声明
		p = strchr(p, ' ');
		p = skipSpace(p); //跳过变量前面的空格
		while ((p = skipSpace(p)), (*p) != '\0'){//p指向一个变量的地址,注意中间的是逗号
			while ((isdigit(p[varLen]) || isalpha(p[varLen]))){
				varLen++;
			}
			if (varLen != 0){
				strncpy(allVarible[varCount].varName, p, varLen); //拷贝变量名称的数组中
				allVarible[varCount].varName[varLen] = '\0';
				allVarible[varCount].val1 = 0.0;
				allVarible[varCount].type = DOUBLE;
				p += varLen;
				varLen = 0;
				varCount++;
			}
			else{
				//printf("shouldn't enter this!/n");
			}
		}
		return 0; //该行读取完毕
	}
	else if (p = line, (strstr(line, "print") == NULL) && (p = strstr(line, "int")) != NULL){//该行是int的声明,注意print这个语句中也是含有int的，要将其排除掉
		p = strchr(p, ' ');
		p = skipSpace(p);
		while ((p = skipSpace(p)), (*p)!= '\0'){//p指向一个变量的地址
			while (isdigit(p[varLen]) || isalpha(p[varLen])){
				varLen++;
			}
			if (varLen != 0){
				allVarible[varCount].varName;
				strncpy(allVarible[varCount].varName, p, varLen); //拷贝变量名称的数组中
				allVarible[varCount].varName[varLen] = '\0'; //字符串以'\0'结尾
				allVarible[varCount].val0 = 0;
				allVarible[varCount].type = INT;
				p += varLen;
				varLen = 0;
				varCount++;
			}
			else{
				//printf("shouldn't enter this!/n");
			}
		}
		return 0; //该行读取完毕
	}
	else{ // reach print, print the ans
		p = strchr(p, '('); //定位到print语句后面的括号
		p++;
		p = skipSpace(p); //跳过括号后面的空格
		if (isdigit(*p)){ //处理纯数字(根据第一个字符是否是整数来进行判断)
			if (strchr(p, '.') == NULL){ //处理的是整数
				while (isdigit(p[varLen])){
					varLen++;
				}
				strncpy(valStr, p, varLen);
				valStr[varLen] = '\0';
				printf("%d\n", atoi(valStr));
			}
			else{//处理的是浮点数
				while (isdigit(p[varLen]) || p[varLen] == '.'){
					varLen++;
				}
				strncpy(valStr, p, varLen);
				valStr[varLen] = '\0';
				printf("%.6f\n", atof(valStr));
			}
			p += varLen;
			varLen = 0;
			memset(valStr, 0, sizeof(valStr));
		}
		else if(isalpha(*p)){ //处理一个变量
			while (isdigit(p[varLen]) || isalpha(p[varLen])){
				varLen++;
			}
			strncpy(valStr, p, varLen);
			valStr[varLen] = '\0';
			p += varLen;
			varLen = 0;
			struct Varible * varTmp = getVarible(valStr);
			if (varTmp->type == DOUBLE){//变量是浮点型
				printf("%.6f\n", varTmp->val1);
			}
			else{
				printf("%d\n", varTmp->val0);
			}
		}
		else{
			//printf("Error, 既不是变量也不是字符！");
		}
	}
	return 0;
}



/*
**func: 计算以及更新变量的值
**arg:	line: 一行内容
**
*/
int getVarCalculate(const char * line)//得到莫一行计算生成的变量的值
{
	struct tokenStack t;
	t.top = 0;
	memset(t.token, 0, sizeof(t.token));

	char RevPolish[MAX_TOKEN][NAME_MAX_LEN]; // 每行的最多的变量的个数
	int tokenCount = 0;
	int varLen = 0;
	char preOp = ' ';//这里表示的是前一个操作符，用来处理两个符号连在一起的情况，例如*-
	char * p = line;
	while ((p = skipSpace(p)), *p != '\0'){
		if (isdigit(*p) || isalpha(*p)){
			while (p != NULL && (isalpha(p[varLen]) || isdigit(p[varLen]) || p[varLen] == '.')){ //不要忘了小数点
				varLen++;
			}
			strncpy(RevPolish[tokenCount], p, varLen);
			p += varLen;
			RevPolish[tokenCount][varLen] = '\0';
			tokenCount++;
			varLen = 0;
		}else if (*p == '('){
			push(&t, '(');
			p++;
		}else if (*p == '*' || *p == '/'){
			while (!isEmpty(&t) && (top(&t) == '*' || top(&t) == '/')){
				RevPolish[tokenCount][0] = pop(&t); //弹出字符
				RevPolish[tokenCount][1] = '\0';
				tokenCount++;
			}
			push(&t, *p);
			p++;
		}else if (*p == '+' || *p == '-'){
			while (!isEmpty(&t) && top(&t) != '=' && top(&t) != '('){
				RevPolish[tokenCount][0] = pop(&t); //弹出字符
				RevPolish[tokenCount][1] = '\0';
				tokenCount++;
			}
			push(&t,*p);
			p++;
		}else if (*p == '='){
			while (!isEmpty(&t) && top(&t) != '(' && top(&t) != '='){
				RevPolish[tokenCount][0] = pop(&t);
				RevPolish[tokenCount][1] = '\0';
				tokenCount++;
			}
			push(&t,*p);
			p++;
		}else if (*p == ')'){
			while (!isEmpty(&t) && top(&t) != '('){
				RevPolish[tokenCount][0] = pop(&t);
				RevPolish[tokenCount][1] = '\0';
				tokenCount++;
			}
			pop(&t); // 弹出'('符号
			p++;
		}else{
			//printf("Get unknown input!!");
			p++;
		}
	}//end of while((p = skipSpace(p)) != NULL)
	while (!isEmpty(&t)){ //读取表达式结束，将堆栈中剩余的所欧符号都放回到逆波兰表达式中
		RevPolish[tokenCount][0] = pop(&t);
		RevPolish[tokenCount][1] = '\0';
		tokenCount++;
	}


	struct tokenStackExp tExp;
	tExp.top = 0;
	memset(tExp.exp, 0, MAX_TOKEN * sizeof(tExp.exp[0]));
	//下面开始计算逆波兰表达式的值：
	int i = 0;
	BOOL isDouble = False;
	double tmpRes = 0.0;
	char tmpResStr[64]; //存放暂时的结果用于入栈
	for (i = 0; i < tokenCount; ++i){
		if (isalpha(RevPolish[i][0]) || isdigit(RevPolish[i][0])){ //得到一个变量的名字或者是一个数值
			pushExp(&tExp, RevPolish[i]);
		}
		else if (RevPolish[i][0] == '+'){
			char * rightOpnd = popExp(&tExp);
			char * leftOpnd = popExp(&tExp);
			if (isdigit(leftOpnd[0]) || leftOpnd[0] == '-'){//是一个纯数字
				if (strchr(leftOpnd, '.') == NULL){//整数
					tmpRes += atoi(leftOpnd);
				}
				else{
					tmpRes += atof(leftOpnd);
					isDouble = True;
				}
			}else{//是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(leftOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					tmpRes += vrb->val1;
				}
				else{
					tmpRes += vrb->val0;
				}
			}

			if (isdigit(rightOpnd[0]) || rightOpnd[0] == '-'){//右操作数是一个纯数字
				if (strchr(rightOpnd, '.') == NULL){//整数
					tmpRes += atoi(rightOpnd);
				}
				else{
					tmpRes += atof(rightOpnd);
					isDouble = True;
				}
			}
			else{//右操作数是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(rightOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					tmpRes += vrb->val1;
				}
				else{
					tmpRes += vrb->val0;
				}
			}
			//下面将结果继续入栈
			if (isDouble){
				floatToStr(tmpRes, tmpResStr);
			}
			else{
				intToStr(tmpRes, tmpResStr);
			}
			pushExp(&tExp, tmpResStr);
			tmpRes = 0.0;
			memset(tmpResStr, 0, sizeof(tmpResStr));
		}
		else if (RevPolish[i][0] == '-'){
			char * rightOpnd = popExp(&tExp);
			char * leftOpnd = popExp(&tExp);
			if (isdigit(leftOpnd[0]) || leftOpnd[0] == '-'){//是一个纯数字
				if (strchr(leftOpnd, '.') == NULL){//整数
					tmpRes += atoi(leftOpnd);
				}
				else{
					tmpRes += atof(leftOpnd);
					isDouble = True;
				}
			}
			else{//是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(leftOpnd);
				if (vrb->type == DOUBLE){
					isDouble =True;
					tmpRes += vrb->val1;
				}
				else{
					tmpRes += vrb->val0;
				}
			}

			if (isdigit(rightOpnd[0]) || rightOpnd[0] == '-'){//右操作数是一个纯数字
				if (strchr(rightOpnd, '.') == NULL){//整数
					tmpRes -= atoi(rightOpnd);
				}
				else{
					tmpRes -= atof(rightOpnd);
					isDouble = True;
				}
			}
			else{//右操作数是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(rightOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					tmpRes -= vrb->val1;
				}
				else{
					tmpRes -= vrb->val0;
				}
			}
			//下面将结果继续入栈
			if (isDouble){
				floatToStr(tmpRes, tmpResStr);
			}
			else{
				intToStr(tmpRes, tmpResStr);
			}
			pushExp(&tExp, tmpResStr);
			tmpRes = 0.0;
			memset(tmpResStr, 0, sizeof(tmpResStr));
		}
		else if (RevPolish[i][0] == '*'){
			char * rightOpnd = popExp(&tExp);
			char * leftOpnd = popExp(&tExp);
			if (isdigit(leftOpnd[0]) || leftOpnd[0] == '-'){//是一个纯数字
				if (strchr(leftOpnd, '.') == NULL){//整数
					tmpRes += atoi(leftOpnd);
				}
				else{
					tmpRes += atof(leftOpnd);
					isDouble = True;
				}
			}
			else{//是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(leftOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					tmpRes += vrb->val1;
				}
				else{
					tmpRes += vrb->val0;
				}
			}

			if (isdigit(rightOpnd[0]) || rightOpnd[0] == '-'){//右操作数是一个纯数字
				if (strchr(rightOpnd, '.') == NULL){//整数
					tmpRes *= atoi(rightOpnd);
				}
				else{
					tmpRes *= atof(rightOpnd);
					isDouble = True;
				}
			}
			else{//右操作数是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(rightOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					tmpRes *= vrb->val1;
				}
				else{
					tmpRes *= vrb->val0;
				}
			}
			if (isDouble){
				floatToStr(tmpRes, tmpResStr);
			}
			else{
				intToStr(tmpRes, tmpResStr);
			}
			pushExp(&tExp, tmpResStr);
			tmpRes = 0.0;
			memset(tmpResStr, 0, sizeof(tmpResStr));
		}
		else if (RevPolish[i][0] == '/'){
			char * rightOpnd = popExp(&tExp);
			char * leftOpnd = popExp(&tExp);
			if (isdigit(leftOpnd[0]) || leftOpnd[0] == '-'){//是一个纯数字
				if (strchr(leftOpnd, '.') == NULL){//整数
					tmpRes += atoi(leftOpnd);
				}
				else{
					tmpRes += atof(leftOpnd);
					isDouble = True;
				}
			}
			else{//是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(leftOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					tmpRes += vrb->val1;
				}
				else{
					tmpRes += vrb->val0;
				}
			}

			if (isdigit(rightOpnd[0]) || rightOpnd[0] == '-'){//右操作数是一个纯数字
				if (strchr(rightOpnd, '.') == NULL){//整数
					if (atoi(rightOpnd) != 0){
						if (isDouble == False){
							tmpRes = (int)tmpRes / (int)(atoi(rightOpnd));
						}
						else{
							tmpRes = (double)tmpRes / (double)(atoi(rightOpnd));
						}
					}
					else
						return DEVIDE_ERROR;
				}
				else{
					if (atof(rightOpnd) == 0.0)
						return DEVIDE_ERROR;
					tmpRes /= atof(rightOpnd);
					isDouble = True;
				}
			}
			else{//右操作数是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(rightOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					if (vrb->val1 == 0.0)
						return DEVIDE_ERROR;
					tmpRes /= vrb->val1;
				}
				else{
					if (vrb->val0 == 0)
						return DEVIDE_ERROR;
					tmpRes /= vrb->val0;
				}
			}
			if (isDouble){
				floatToStr(tmpRes, tmpResStr);
			}
			else{
				intToStr(tmpRes, tmpResStr);
			}
			pushExp(&tExp, tmpResStr);
			tmpRes = 0.0;
			memset(tmpResStr, 0, sizeof(tmpResStr));
		}
		else if (RevPolish[i][0] == '='){
			char * rightOpnd = popExp(&tExp);
			char * leftOpnd = popExp(&tExp);
			if (isdigit(rightOpnd[0]) || rightOpnd[0] == '-'){//右操作数是一个纯数字
				if (strchr(rightOpnd, '.') == NULL){//整数
					tmpRes += atoi(rightOpnd);
				}
				else{
					tmpRes += atof(rightOpnd);
					isDouble = True;
				}
			}else{//右操作数是一个变量名，到数组中去寻找
				struct Varible * vrb = getVarible(rightOpnd);
				if (vrb->type == DOUBLE){
					isDouble = True;
					tmpRes += vrb->val1;
				}
				else{
					tmpRes += vrb->val0;
				}
			}
			struct Varible * vrb = getVarible(leftOpnd); //左操作数一定是个变量
			if (vrb->type == DOUBLE){
				isDouble = True;
				vrb->val1 = tmpRes; //将值赋值给左边
			}
			else{
				vrb->val0 = tmpRes;
			}
			pushExp(&tExp, leftOpnd);
			tmpRes = 0.0;
			memset(tmpResStr, 0, sizeof(tmpResStr));
		}
		else{
			printf("Unknown Token!!!\n");
		}
	}
	//printf("The expression process to the end!!\n");
	return 0;
}



/*
**func: 浮点数转换成字符串
**arg:	val: 浮点数的值
**
*/
char * floatToStr(float val, char *buf)
{
	sprintf(buf, "%.6f", val); //精度为6
	return buf;
}



/*
**func: 整数转换成字符串
**arg:	val: 整数的值
**
*/
char * intToStr(int val, char *buf)
{
	sprintf(buf, "%d", val); //精度为6
	return buf;
}


/*
**func: 从变量数组中得到一个变量
**arg:	name: 变量名称
**
*/
struct Varible * getVarible(const char * name)//寻找指定的变量是否存在，然后返回其值
{
	int i = 0;
	for (; i < varCount; ++i){
		if (strcmp(name, allVarible[i].varName) == 0){
			return &allVarible[i];//返回这个变量所在的地址
		}
	}
	//printf("Can't find the target Varible!");
	return 0;
}


/*
**func: 跳过空白以及无关自负
**arg:	line: 一行
**
*/
char * skipSpace(const char * line)
{
	char * p = line;
	while (p != NULL && (isspace(p[0]) || p[0] == ',' || p[0] == ';')){ //判断是否到达行尾部
		p++;
	}
	return p; //当前指针指向不是空格的第一个自读
}
