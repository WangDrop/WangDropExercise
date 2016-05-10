public class Solution {
    public int minSubArrayLen(int s, int[] nums) {
        if(nums.length == 0)
            return 0;
        int subSum = nums[0];
        int ret = Integer.MAX_VALUE;
        int p1 = 1, p2 = 0;
        while(p2 < p1){
            if(subSum < s){　　//达不到k，指针前移动或者移动到头直接返回
                if(p1 < nums.length){
                    subSum += nums[p1];
                    p1++;
                }else{
                    if(ret == Integer.MAX_VALUE)
                        return 0;
                    return ret;
                }
            }else{　　　　　　//达到k，后指针向前移动并且考虑是否更新指针。
                ret = Math.min(ret, p1-p2);
                subSum -= nums[p2];
                p2++;
            }
        }
        if(ret == Integer.MAX_VALUE) //如果没有找到合适的子数组的话，直接返回0
            return 0;
        return ret;
    }
}