class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0) return 0;
        int szHor = grid.size();
        int szVer = grid[0].size();
        vector<vector<int>> ret = grid;
        ret[0][0] = grid[0][0]
        for(int i = 1; i < szHor; ++i){
            ret[i][0] = ret[i - 1][0] + grid[i][0];
        }

        for(int i = 1; i < szVer; ++i){
            ret[0][i] = ret[0][i - 1] + grid[0][i];
        }
        
        for(int i = 1; i < grid.size(); ++i){
            for(int j = 1; j < grid[0].size(); ++j){
                ret[i][j] = min(ret[i - 1][j], ret[i][j - 1]) + grid[i][j];
            }
        }
        return ret[szHor - 1][szVer - 1];
    }
};