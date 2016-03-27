class Solution {
        public:
        vector<TreeNode*> generateTrees(int n) {
                    return createNode(1, n);       
        }
    vector<TreeNode*> createNode(int start, int end)
            {
                    vector<TreeNode*> result;
            if(start > end){
                            result.push_back(NULL);
                            return result;
                        
            }
            for(int i = start; i <= end; ++i){
                            vector<TreeNode*> leftNode = createNode(start, i - 1);
                            vector<TreeNode*> rightNode = createNode(i + 1, end);
                for(int j = 0; j < leftNode.size(); ++j){
                    for(int k = 0; k < rightNode.size(); ++k){
                                            TreeNode * tmpNode = new TreeNode(i);
                                            tmpNode->left = leftNode[j];　　
                                            tmpNode->right = rightNode[k];
                                            result.push_back(tmpNode);
                                        
                    }
                                
                }
                        
            }
                    return result;
                
        }
};
