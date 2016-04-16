public class Solution {
    public boolean isPalindrome(String s) {
         int sz = s.length();
         int beg = 0, end = sz - 1;
         while(beg < end){
             while(!Character.isLetter(s.charAt(beg)) && !Character.isDigit(s.charAt(beg))){
                 if(beg < end) beg++;
                 else return true;
             }
             while(!Character.isLetter(s.charAt(end)) && !Character.isDigit(s.charAt(end))){
                 if(beg < end) end--;
                 else return true;
             }
             if(Character.toUpperCase(s.charAt(beg)) == Character.toUpperCase(s.charAt(end))){
                 beg++;
                 end--;
             }else{
                 return false;
             }
         }
         return true;   
    }
}