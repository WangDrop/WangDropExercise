class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int pos = 0;
        int sz = nums.size();
        for (int i = 0; i < sz; ++i){
            if (nums[i] != val){
                nums[pos++] = nums[i];
            }
        }
        return pos;
    }
};