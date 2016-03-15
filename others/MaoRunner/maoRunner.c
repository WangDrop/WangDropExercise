#include "maoRunner.h"
extern int varCount;
extern struct Varible allVarible[4096];
extern char fileContent[MAX_LINE][MAX_LINE_LEN];
extern int lineCount;

int main(int argc, char ** argv)
{
	if(argc < 2){
		return;
	}else{
		getContent(argv[1]);//读取文件内容
		int i = 0;
		for(i = 0; i < lineCount; ++i){
        if(DEVIDE_ERROR == getVarValue(fileContent[i]))//如果除法出错，那么不再继续向下处理
				break;
    	}
	}
	return 0;
}
