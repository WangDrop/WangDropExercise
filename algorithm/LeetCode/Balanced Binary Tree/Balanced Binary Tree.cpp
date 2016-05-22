/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        int dep;
        checkBalance(root, dep);
    }
    bool checkBalance(TreeNode * root, int &dep)
    {
        if(root == NULL){
            dep = 0;
            return true;
        }
        int leftDep, rightDep;
        bool isLeftBal = checkBalance(root->left, leftDep);
        bool isRightBal = checkBalance(root->right, rightDep);

        dep = max(leftDep, rightDep) + 1;
        return isLeftBal && isRightBal && (abs(leftDep - rightDep) <= 1);
    }
};