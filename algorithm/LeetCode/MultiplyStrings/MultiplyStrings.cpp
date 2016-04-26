class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int steps = 0;
        int pos = 0;
        int flag = 0;
        int val = 0;
        string result = "";
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int len1 = num1.length();
        int len2 = num2.length();
        for(int i = 0; i < len1; ++i){
              pos = steps;
            for(int j = 0; j < len2; ++j){
                val = (num1[i] - '0')*(num2[j] - '0') + flag;
                if(result.size() <= pos){
                    result.append(1, val%10 + '0');
                }else{
                    val += (result[pos] - '0');
                    result[pos] = val%10 + '0';
                }
                flag = val/10;
                pos++;  
            }
            if(flag > 0)
                result.append(1, flag + '0');
            flag = 0;
            steps++;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};