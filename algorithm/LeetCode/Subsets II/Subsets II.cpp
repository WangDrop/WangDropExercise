class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
          ret.clear();
          tmp.clear();
          rawVec = nums;
          sort(rawVec.begin(), rawVec.end());
          dfs(0);
          return ret;
    }

    void dfs(int start)
    {
        ret.push_back(tmp); //首先push一个空集
        for(int i = start; i < rawVec.size(); ++i){
            if(i != start && rawVec[i] == rawVec[i - 1]) continue;  //这里的i != start；应该注意
            tmp.push_back(rawVec[i]);
            dfs(i + 1);
            tmp.pop_back();
        }
    }
private:
    vector<vector<int>> ret;
    vector<int> tmp;
    vector<int> rawVec;

};