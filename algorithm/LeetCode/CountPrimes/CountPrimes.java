public class Solution {
    public int countPrimes(int n) {
        int [] prime = new int[n+1]; //这里其实用boolean更好，懒得改了
        int count = 0;
        for(int i = 0; i < n+1; ++i){
            prime[i] = i;
        }
        for(int i = 2; i < n+1; ++i){
            if(prime[i] == -1)
                continue;
            else{
                count++;
                for(int mul = 2; mul * i < n+1; ++mul){
                    prime[mul*i] = -1;
                }
            }
        }
        return count;
    }
}