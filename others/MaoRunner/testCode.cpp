// Test the getVarDeclare;
//char *s = "double ee,ff,gg;";
//int i = 0;
//getVarDeclare(s);
//for (i = 0; i < varCount; ++i){
//	printf("%d : The name of the vrb is %s, the type is %d\n",
//		i, allVarible[i].varName, allVarible[i].type);
//}


//Test the getContent
//getContent("S3.txt");
//int i = 0;
//for (i = 0; i < lineCount; ++i){
//	printf("Current is line %d, the content is : %s", i + 1, fileContent[i]);
//}
//system("pause");


//读取文件以及打印功能的处理
//const char * line1 = "int y;";
//const char * line2 = "print(y);";
//const char * line3 = "double x, y;";
//getVarValue(line1);
//getVarValue(line2);
//getVarValue(line3);


//下面是重头戏，计算表达式
//const char * line1 = "int a, d;";
//const char * line = "(a) = a + (d = 3.5 + 4.5);";
//const char * line2 = "print(a);";
//const char * line3 = "print(d)";
//getVarValue(line1);
//getVarValue(line);
//getVarValue(line2);
//getVarValue(line3);


//测试整体的功能
//getContent("S3.txt");
//printf("The line is : %d", lineCount);
//int i = 0;
//for (i = 0; i < lineCount; ++i){
//	getVarValue(fileContent[i]);
//}