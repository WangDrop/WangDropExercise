class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sz = nums.size();
        int total = (sz + 1)*sz / 2;
        for (int i = 0; i < sz; ++i){
            total -= nums[i];
        }
        return total;
    }
};