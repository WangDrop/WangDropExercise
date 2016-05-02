class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int beg = 0;
        int end = nums.size() - 1;
        int mid;
        while(beg <= end){
            mid = (beg + end) >> 1;
            if(nums[mid] > target)
                end = mid - 1;
            else if(nums[mid] < target)
                beg = mid + 1;
            else
                return mid;
        }
        int sz = nums.size();
        if(end < 0) reutrn 0;    //这个地方应该注意，不要搞反了
        if(beg >= sz) reutrn sz;
        return beg;    //这一步应该注意，很关键
    }
};