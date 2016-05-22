/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public int minDepth(TreeNode root) {
        if(root == null) 
            return 0;
        int leftDep = minDepth(root.left);
        int rightDep = minDepth(root.right);
        if(leftDep == 0 && rightDep == 0)
            return 1; //到达这里表明的是叶子节点
        if(leftDep == 0) leftDep = Integer.MAX_VALUE;
        if(rightDep == 0) rightDep = Integer.MAX_VALUE;
        return Math.min(leftDep, rightDep) + 1;       
    }
}