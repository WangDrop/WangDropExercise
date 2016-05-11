class Solution {
public:
    int rob(vector<int>& nums) {
        int sz = nums.size();
        vector<int> maxRet = nums;
        if(sz == 0) return 0;
        if(sz == 1) return nums[0];
        if(sz == 2) return max(nums[0], nums[1]);
        int i;
        maxRet[0] = nums[0];
        maxRet[1] = max(nums[0], nums[1]);
        for(i = 2; i < sz; ++i){
            maxRet[i] = max(maxRet[i - 2] + nums[i], maxRet[i - 1]);
        }
        return maxRet[i - 1];
    }
};