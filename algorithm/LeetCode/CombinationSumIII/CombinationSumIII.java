public class Solution {
    public List<List<Integer>> combinationSum3(int k, int n) {
        List<List<Integer>> ret = new ArrayList<List<Integer>>();
        List<Integer> tmp = new ArrayList<Integer>();
        dfs(ret, tmp, 0, k, 1, n); 
        return ret;  
    }
    
    public void dfs(List<List<Integer>>ret, List<Integer>tmp, int dep, int maxDep, int start, int left){
        if(left < 0)
            return; //回溯
        else if(left == 0){
            if(dep == maxDep)
                ret.add(new ArrayList<Integer>(tmp));
            return;
        }else{
            for(int i = start; i <= 9; ++i){
                tmp.add(i);
                dfs(ret, tmp, dep+1, maxDep, i+1, left - i);
                tmp.remove(new Integer(i));
            }
        }
    }
}