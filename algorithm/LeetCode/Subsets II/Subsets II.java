public class Solution {
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> ret = new ArrayList<List<Integer>>();
        List<Integer> tmp = new ArrayList<Integer>();    
        dfs(ret, tmp, nums, 0, nums.length);
        return ret;
    }
    
    public void dfs(List<List<Integer>> ret, List<Integer> tmp, int [] nums, int start, int limit){
        if(start > limit)
            return;
        else if(start == limit){
            ret.add(new ArrayList<Integer>(tmp));
            return;
        }else{
            ret.add(new ArrayList<Integer>(tmp));
            for(int i = start; i < limit; ++i){
                tmp.add(nums[i]);
                dfs(ret, tmp, nums, i+1, limit);
                tmp.remove((Integer)nums[i]);
                while(i+1 < limit && nums[i+1] == nums[i]) //跳过所有的重复的数字
                    i++; //这里加完了之后while循环又会再加一次，正好跳过所有的重复的值
            }
        }
    }
}