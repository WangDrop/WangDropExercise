class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        tmpCdd = candidates;
        sort(tmpCdd.begin(), tmpCdd.end());
        this->target = target;
        vector<int> tmpVec;
        dfs(0, tmpVec);
        return result;
    }    
private:
    int target;
    vector<int> tmpCdd;
    vector<vector<int>> result;
private:
    void dfs(int index, vector<int> & tmpVec)
    {
        if(index == tmpCdd.size()) return;    //到达叶节点
        int tmpSum = accumulate(tmpVec.begin(), tmpVec.end(), 0);
        if(tmpSum == target){
            result.push_back(tmpVec);
            return;
        }else if(tmpSum > target){//剪枝
            return;
        }else{
            for(int i = index; i < tmpCdd.size(); ++i){//这里从i开始的原因是因为参数可以是重复的
                tmpVec.push_back(tmpCdd[i]);
                dfs(i, tmpVec);
                tmpVec.pop_back();//回溯
            }
        }
    }
};