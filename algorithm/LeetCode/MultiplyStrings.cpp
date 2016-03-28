class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") 
        	return "0";
        int startPos = 0;//相乘的开始位置
        int pass; //向前的进位
        int currPos = 0; //当前的位置
        int mulNum = 0;
        string res;
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int len1 = num1.size();
        int len2 = num2.size();
        for(int i = 0; i < len2; i++, startPos++){
        	currPos = startPos;
        	pass = 0;
        	for(int j = 0; j < len1; ++j){
        		if(res.size() <= currPos)
        			res += "0";
        		mulNum = (num1[j] - '0')*(num2[i] - '0') + pass;
        		int tmp = (res[currPos] - '0') + mulNum;
        		if(tmp >= 10){
        		    res[currPos] = tmp%10 + '0';
        			pass = tmp/10;
        		}else{
        		    res[currPos] = tmp + '0';
        		    pass = 0;
        		}
        		currPos++;
        	}
        	if(pass != 0){
        		if(res.size() <= currPos)
        			res += "0";
        		res[currPos] += pass;
        	}
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
