> 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。 例如 a b c e s f c s a d e e 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。

public class Solution {
    private int [][] arr = new int[][]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    private boolean [][] mark;
    public boolean hasPath(char[] matrix, int rows, int cols, char[] str){
    	mark = new boolean[rows][cols];
        boolean res = false;
        for(int i = 0; i < rows; ++i)
            for(int j = 0; j < cols; ++j){
            	mark[i][j] = true;
        		res = dfs(matrix, i * cols + j, 0, rows, cols, str, mark);
            	mark[i][j] = false;
        		if(res)
                    return true;
        	}
        return false;
    }
    
    boolean dfs(char [] matrix, int matrixIndex,int strIndex, int rows, int cols, char [] str, boolean [][] mark){
        if(strIndex == str.length - 1 && matrix[matrixIndex] == str[strIndex])
            return true;
        if(matrix[matrixIndex] != str[strIndex])
            return false;
        int tmpIndex, x, y;
        boolean res = false;
        for(int i = 0; i < 4; ++i){
            tmpIndex = matrixIndex + cols * arr[i][0] + arr[i][1];
            x = tmpIndex/cols;
            y = tmpIndex%cols;
            if(x >= 0 && x < rows && y >= 0 && y < cols && mark[x][y] == false){
                mark[x][y] = true;
                res = dfs(matrix, tmpIndex, strIndex + 1, rows, cols, str, mark);
                mark[x][y] = false;
            }
            if(res == true)
				return true;
        }
        return false;
    }
}

地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？
public class Solution {
    boolean [][] mark = null;
    int [][] direc = new int[][]{{-1,0},{0,1},{1,0},{0,-1}};
    int count = 0;
    public int movingCount(int threshold, int rows, int cols){
        if(rows == 0 || cols == 0)
            return 0;
        if(threshold == 0)
            return 1; // for (0,0)
        mark = new boolean[rows][cols];
        mark[0][0] = true;
        dfs(0,0,rows,cols,mark,threshold);
        return count;
    }
    
    public void dfs(int x, int y, int rows, int cols, boolean [][] mark, int threshold){
        if(checkValue(x,y,threshold))
            count++;
        else return;
        int xx, yy;
        for(int i = 0; i < 4; ++i){
            xx = x + direc[i][0];
            yy = y + direc[i][1];
            if(xx >= 0 && xx < rows && yy >= 0 && yy < cols && !mark[xx][yy]){
                mark[xx][yy] = true;
                dfs(xx, yy, rows, cols, mark, threshold);
            }
        }
    }

	boolean checkValue(int x, int y, int threshold){
        int count = 0;
        while(x != 0){
            count += x % 10;
            x /= 10;
        }
        while(y != 0){
            count += y % 10;
            y /= 10;
        }
        if(count <= threshold)
            return true;
        return false;
        
    }
}