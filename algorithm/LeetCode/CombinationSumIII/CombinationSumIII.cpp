class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n){
        size = k;
        target = n;
        vector<int> tmpVec;
        tmpVec.clear();
        ret.clear();
        dfs(tmpVec, target, 1);
        return ret;
    }
    void dfs(vector<int>& vec, int left, int start)
    {
        if(left < 0) return;
        if(left == 0 && vec.size() == size){ 
            ret.push_back(vec);
            return;
        }
        for(int i = start; i <= 9; ++i){
            vec.push_back(i);
            dfs(vec, left - i, i + 1);
            vec.pop_back();
        }
    }
private:
    vector<vector<int>> ret;
    int target;
    int size;
};