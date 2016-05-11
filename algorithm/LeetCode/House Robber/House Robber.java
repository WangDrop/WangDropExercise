public class Solution {
    public int rob(int[] nums) {
        int sz = nums.length;
        if(sz == 0) 
            return 0;
        if(sz == 1) 
            return nums[0];
        if(sz == 2) 
            return Math.max(nums[0], nums[1]);
        int [] ret = new int [sz];
        ret[0] = nums[0];
        ret[1] = Math.max(nums[0], nums[1]);
        for(int i = 2; i < sz; ++i){
            ret[i] = Math.max(ret[i-2] + nums[i], ret[i-1]);
        }
        return ret[sz-1];
    }
}