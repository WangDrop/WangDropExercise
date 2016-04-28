public class Solution {
    public int missingNumber(int[] nums) {
        int sum = nums.len * (nums.len + 1)/2; //length大小是n-1
        for(int i = 0; i < nums.length; ++i){
            sum -= nums[i];
        }
        return sum;
    }
}