public class Solution {
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        List<List<Integer>> ret = new ArrayList<List<Integer>>();
        Arrays.sort(candidates);
        for(int i = 0; i < candidates.length; ++i){
            List<Integer> curr = new ArrayList<Integer>();
            if(i != 0 && candidates[i] == candidates[i-1])   //注意这里和下面同样的地方，防止出现相同的组合
                continue;
            curr.add(candidates[i]);
            getCombination(ret, i + 1, target - candidates[i], curr, candidates);
            curr.remove(curr.size() - 1);
        }
        return ret;
    }
    public void getCombination(List<List<Integer>> ret, int index, int target, List<Integer> tmpCdd, int [] candidates){
        if(index > candidates.length)
            return;
        if(target < 0){
            return;
        }else if(target == 0){
            ret.add(new ArrayList<Integer>(tmpCdd));
            return;
        }else{
            for(int i = index; i < candidates.length; ++i){
                if(i != index && candidates[i] == candidates[i-1])
                    continue;
                tmpCdd.add(candidates[i]);
                getCombination(ret, i + 1, target - candidates[i], tmpCdd, candidates);
                tmpCdd.remove(tmpCdd.size() - 1);
            }
        }
    }
}