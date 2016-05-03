public class Solution {
    List<List<Integer>> ret = new ArrayList<List<Integer>>();
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        Arrays.sort(candidates);
        for(int i = 0; i < candidates.length; ++i){
            ArrayList<Integer> tmpCdd = new ArrayList<Integer>();
            tmpCdd.add(candidates[i]);
            dfs(i, tmpCdd, candidates, target - candidates[i]);
            tmpCdd.remove(tmpCdd.size() - 1);
        }
        return ret;
    }

    public void dfs(int index, List<Integer> tmpCdd, int[] candidates, int target){
        if(index == candidates.length)
            return;
        if(target < 0)
            return; //直接剪枝
        if(target == 0){
            ret.add(new ArrayList<Integer>(tmpCdd));
            return;
        }else{
            for(int i = index; i < candidates.length; ++i){
                tmpCdd.add(candidates[i]);
                dfs(i, tmpCdd, candidates, target - candidates[i]);
                tmpCdd.remove(tmpCdd.size() - 1);
            }
        }
    }
}