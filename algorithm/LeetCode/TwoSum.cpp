class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> index;
        vector<int> result;
        int sz = nums.size();
        for (int i = 0; i < sz; ++i){
            index[nums[i]] = i;
        }
        map<int, int>::iterator it;
        for (int i = 0; i < sz; ++i){
            if ((it = index.find(target - nums[i])) != index.end()){
                if (it->second == i) continue;//这一步要注意，防止找到的index与当前的i是相等的
                result.push_back(i + 1);
                result.push_back(it->second + 1);
                break;
            }
        }
        return result;
    }
};