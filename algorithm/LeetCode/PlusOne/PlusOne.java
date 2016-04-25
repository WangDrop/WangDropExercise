public class Solution {
    public int[] plusOne(int[] digits) {
         int carry = 1;
         for(int i = digits.length-1; i >= 0; --i){
             int val = digits[i] + carry;
             carry = 0;
             digits[i] = val%10;
             carry = val/10;
         }
         if(carry > 0){
             int [] ret = new int[digits.length + 1];
             ret[0] = carry;
             System.arraycopy(digits, 0, ret, 1, digits.length);
             return ret;
         }
         return digits;
    }
}