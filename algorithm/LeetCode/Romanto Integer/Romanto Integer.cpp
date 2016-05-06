class Solution {
public:
    int romanToInt(string s) {
        int prev, curr, result, tmpResult;
        prev = curr = result = tmpResult = 0;
        int sz = s.size();
        if(sz == 0)
            return 0;
        tmpResult = prev = getRoman(s[0]);
        for(int i = 1; i < sz; ++i){
            curr = getRoman(s[i]);
            if(curr > prev)
                tmpResult =  curr - prev;
            else if(curr == prev)
                tmpResult += curr;
            else{
                result += tmpResult;
                tmpResult = curr;
            }
            prev = curr;
        }
        return result + tmpResult;
    }
    
    int getRoman(char c)
    {
        switch(c){
            case 'I':
                return 1; 
            case 'V':
                return 5; 
            case 'X':
                return 10; 
            case 'L':
                return 50;
            case 'C':
                return 100;
            case 'D':
                return 500;
            case 'M':
                return 1000;//题目说了，最多只能到4999，不用取更大的了 
            default:
                return 0;
        }
    }
};