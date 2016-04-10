class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int sz = nums.size();
        sort(nums.begin(), nums.end());//当然了，首先还是要排序的
        int diff = INT_MAX;//这个直接取INT_MAX,这样计算出来的diff一定是比这个要小的
        int tmpDiff;
        int ans;
        int beg, end;
        for (int i = 0; i < sz - 2; ++i){
            beg = i + 1, end = sz - 1;
            while (beg < end){
                int sum = nums[i] + nums[beg] + nums[end];
                if ((tmpDiff = abs(sum - target)) < diff){
                    diff = tmpDiff;
                    ans = sum;
                }
                if (sum > target){
                    end--;
                }
                else if (sum < target){
                    beg++;
                }
                else
                    return sum;//相等的话就直接返回了
            }
        }
        return ans;
    }
};