class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        tmpCdd = candidates;
        sort(tmpCdd.begin(), tmpCdd.end());
        vector<int> tmpVec;
        dfs(tmpVec, 0, target);//这个dfs的参数分别是当前vec中含有的元素数目
        return result;            //序号起始以及，距离target还差的数目
    }
private:
    vector<int> tmpCdd;
    vector<vector<int>> result;
    void dfs(vector<int> & tmpVec, int index, int tgt)
    {
        if(tgt == 0){
            result.push_back(tmpVec);
            return;            //达到target，剪枝
        }
        if(index == tmpCdd.size()) return;
        else{
            for(int idx = index; idx < tmpCdd.size(); ++idx){
                if (idx != index && tmpCdd[idx] == tmpCdd[idx - 1])
                    continue;    //这一步的主要目标是防止相邻相同的数和其他数一起匹配成为多个相同的vector，很关键。
                if(tmpCdd[idx] <= tgt){
                    tmpVec.push_back(tmpCdd[idx]);    //这其他的实际上和combinationSum1是相同的
                    dfs(tmpVec, idx + 1, tgt - tmpCdd[idx]);
                    tmpVec.pop_back();
                }
            }
        }
    }
};