public class Solution {
    public int numSquares(int n) {
        int [] dp = new int[n+1];
        for(int i = 0; i < n + 1; ++i){
            dp[i] = i;
        }
        for(int i = 0; i < n+1; ++i){
            for(int j = 2; j <= Math.sqrt(i); ++j){
                if(j*j == i){
                    dp[i] = 1;
                    break;
                }
                dp[i] = Math.min(dp[i], 1 + dp[i - j * j]);
            }
        }
        return dp[n];
    }
}