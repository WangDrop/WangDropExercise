public class Solution{
    int [] num = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    String [] roman = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    public String intToRoman(int n) {
        StringBuffer str = new StringBuffer("");
        for(int i = 0; n != 0; ++i){
            while (n >= num[i]) {
                n -= num[i];
                str.append(roman[i]);
            }
        }
        return str.toString();
    }
}