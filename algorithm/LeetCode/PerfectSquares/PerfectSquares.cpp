class Solution {
public:
    int numSquares(int n) {
        vector<int> pSqr(n + 1, 0);
        for (int i = 0; i < n + 1; ++i){
            pSqr[i] = i;//这里取i一定是最大值了，应为至少也可以全由1来组成，相当于背包问题里面的0
        }
        for (int i = 0; i < n + 1; ++i){
            for (int j = 2; j <= sqrt(i); ++j){//从2开始是有原因的，应为i= 1，2，3的时候就是pSqr的值，这里就不用算了
                if (j * j == i){ pSqr[i] = 1; break; }
                pSqr[i] = min(pSqr[i], 1 + pSqr[i - j * j]);//这一步是关键
            }
        }
        return pSqr[n];
    }
};