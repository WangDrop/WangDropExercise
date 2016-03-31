class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        vector<vector<int>> result;
        int sz = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < sz - 2; ++i){
            twoSum(nums, i + 1, 0 - nums[i], result);
            while(nums[i] == nums[i + 1]) ++i;//这一步要注意，防止得出重复的vector
        }
        return result;
    }
    
    void twoSum(vector<int> & nums, int start, int value, vector<vector<int>> & ret)
    {
        int beg = start;
        int end = nums.size()-1;
        while (beg < end){
            int sum = nums[beg] + nums[end];
            if (sum < value)
                beg++;
            else if (sum > value)
                end--;
            else{
                ret.push_back(vector<int>{nums[start - 1], nums[beg], nums[end]});
                while (nums[beg + 1] == nums[beg]) beg++;//这一步的处理应该注意，防止出现相同的vector
                while (nums[end - 1] == nums[end]) end--;
                beg++, end--;
            }
        }
    }
};