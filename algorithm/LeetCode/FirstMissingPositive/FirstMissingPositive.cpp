class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sz = nums.size();
        if(sz == 0) return 1;
        int index;
        for (index = 0; index < sz; index++){
            if (nums[index] <= 0)
                continue;
            else
                break;
        }
        if (nums[index] != 1 || index == sz) return 1;  //当没有正数的情况或正数的第一个数不是1的情况
        while (index < sz){
            if (nums[index + 1] != nums[index] && nums[index + 1] != nums[index] + 1) //两个判断主要是为了防止vector中重复的数字出现。
                return nums[index] + 1;
            index++;
        }
        return nums[index] + 1;
    }
};