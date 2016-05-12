public class Solution {
    public int minPathSum(int[][] grid) {
        if(grid.length == 0 || grid[0].length == 0)
            return 0;        
        int szRol = grid.length;
        int szCol = grid[0].length;
        int [][] ret = new int [szRol][szCol];
        ret[0][0] = grid[0][0];
        for(int i = 1; i < szRol; ++i){
            ret[i][0] = ret[i-1][0] + grid[i][0];
        }
        for(int i = 1; i < szCol; ++i){
            ret[0][i] = ret[0][i-1] + grid[0][i];  
        }
        for(int i = 1; i < szRol; ++i){
            for(int j = 1; j < szCol; ++j){
                ret[i][j] = Math.min(ret[i-1][j], ret[i][j-1]) + grid[i][j];       
            }
        }
        return ret[szRol-1][szCol-1];
    }
}