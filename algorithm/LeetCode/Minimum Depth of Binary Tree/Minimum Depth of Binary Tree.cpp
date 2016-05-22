class Solution{
public:
	int MinDepth(TreeNode * root){
		if(root == null)
			return 0;
		int leftDep = MinDepth(root->left);
		int rightDep= MinDepth(root->right);
		if(leftDep == NULL && rightDep == NULL)
			return 1;
		if(!leftDep) leftDep = INT_MAX;
		if(!rightDep) rightDep = INT_MAX;
		return min(leftDep, rightDep) + 1; 
	}
}