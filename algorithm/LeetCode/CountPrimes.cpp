class Solution {
public:
    int countPrimes(int n) {
        vector<int> vtor(n + 1, 0);
        vector<int> ret;
        for (int i = 0; i <= n; ++i)
            vtor[i] = i;
        for (int i = 2; i < n; ++i){//边界条件注意
            if (vtor[i] != -1){
                ret.push_back(vtor[i]);
                int tmpPrime = vtor[i];
                for (int mul = 1; tmpPrime * mul <= n; mul++){
                    vtor[tmpPrime * mul] = -1;
                }
            }
        }
        return ret.size();
    }
};