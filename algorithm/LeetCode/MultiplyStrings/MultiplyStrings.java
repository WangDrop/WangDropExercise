public class Solution {
    public String multiply(String num1, String num2) {
        if(num1.equals("0") || num2.equals("0"))
            return (new String("0"));
        int step = 0;
        int pos = 0;
        int carry = 0;
        int val = 0;
        String result = new String("");
        num1 = ReverseStr(num1);
        num2 = ReverseStr(num2);
        for(int i = 0; i < num1.length(); ++i){ //java的api好乱啊,一会是length一会有是size()
            pos = step;
            for(int j = 0; j < num2.length(); ++j){
                val = (num1.charAt(i)-'0')*(num2.charAt(j)-'0') + carry;
                if(pos >= result.length())
                    result += (char)(val%10 + '0');
                else{
                    val += (result.charAt(pos)-'0');
                    result = (new StringBuffer(result)).replace(pos, pos + 1, "" + (char)(val%10+'0')).toString();
                }
                carry = val/10;
                pos++;
            }
            if(carry != 0)
                result += (char)(carry +'0');
            carry = 0;
            step++;
        }
        return ReverseStr(result);
        
    }

    public String ReverseStr(String str){
        return (new StringBuffer(str)).reverse().toString();
    }
    
}