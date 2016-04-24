public class Solution {
    public String addBinary(String a, String b) {
        int len1 = a.length();
        int len2 = b.length();
        String ret = new String();
        int i = 0;
        int carry = 0;
        a = ReverseStr(a);
        b = ReverseStr(b);
        while(i < len1 || i < len2 || carry != 0){
            int val = ((i<len1)?(a.charAt(i)-'0'):0) + ((i<len2)?(b.charAt(i)-'0'):0) + carry;
            carry = 0;
            if(val > 1){
                carry = val/2;
                ret += (char)((val%2) + '0');
            }else{
                ret += (char)(val + '0');
            }
            i++;
        }
        return ReverseStr(ret);
    }

       public String ReverseStr(String str){
        return new StringBuffer(str).reverse().toString();
    }
}