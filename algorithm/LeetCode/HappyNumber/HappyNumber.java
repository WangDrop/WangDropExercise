public class Solution {
    public boolean isHappy(int n) {
        HashSet<Integer> set = new HashSet<Integer>();
        do{
            if(set.contains(n))
                return false;
            set.add(n);
            int tmp = 0;
            while(n != 0){
                tmp += (n%10)*(n%10);
                n/=10;
            }
            n = tmp;
        }while(n!=1);
        return true;
    }
}