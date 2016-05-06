public class Solution {
    public int romanToInt(String s) {
         int prev, curr, tmpRes, ret;
         prev = curr = tmpRes = ret = 0;
         int sz = s.length();
         if(sz == 0)
             return 0;
         tmpRes = prev = RToI(s.charAt(0));
         for(int i = 1; i < sz; ++i){
             curr = RToI(s.charAt(i));
             if(curr < prev){
                 ret += tmpRes;
                 tmpRes = curr;
             }else if(curr > prev){
                 tmpRes = curr - prev;
             }else{
                 tmpRes += curr;
             }
             prev = curr;
         }
         return ret + tmpRes;
    }

    public int RToI(char c){
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
                return 1000;//给出数字小于5000，无需在大
            default:
                return 0;
        }
    }
}