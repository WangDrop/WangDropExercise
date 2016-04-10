public class Solution {
    public int threeSumClosest(int[] nums, int target) {
         int len = nums.length;
         int ret = 0;
         int diff = Integer.MAX_VALUE;
         Arrays.sort(nums);
        for(int i = 0; i < len - 2; ++i){
            int beg = i + 1;
            int end = len - 1;
            while(beg < end){
                int tmp = nums[i] + nums[beg] + nums[end];
                int tmpDiff  = Math.abs(tmp - target);
                if(tmpDiff < diff){
                    ret = tmp;
                    diff = tmpDiff;
                }
                if(tmp < target)
                    beg++;
                else if(tmp > target)
                    end--;
                else
                    return target;
            }
        }   
        return ret;
    }
}