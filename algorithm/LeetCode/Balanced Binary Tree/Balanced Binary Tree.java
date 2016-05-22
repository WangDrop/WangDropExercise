/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
public class Solution {
    public boolean isBalanced(TreeNode root) {
        if(root == null)
            return true; 
        if(root.left == null && root.right == null)
            return true;
        if(Math.abs(getDep(root.left) - getDep(root.right)) > 1)
            return false;
        return isBalanced(root.left) && isBalanced(root.right);
    }
    
    
    public int getDep(TreeNode node){
        if(node == null)
            return 0;
        else
            return 1 + Math.max(getDep(node.left), getDep(node.right));
    }
}