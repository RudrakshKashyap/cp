//inorder    left root right

https://www.youtube.com/watch?v=9ChGER8A3Ps&t=343s

Tree* cur = root;

while(cur)
{
    if (cur->left)
    {
        Tree* pre = cur->left;
        while (pre->right && pre->right != cur)
            pre = pre->right;

        if (pre->right)
        {
            pre->right = nullptr;
            
            //cout << cur->val << '\n'; //uncomment for inorder, before going to right we are printing
            cur = cur->right;
        }
        else
        {
            pre->right = cur;

            //cout << cur->val << '\n'; //uncomment for pre order, before going to left we are printing
            cur = cur->left;
        }
    }
    else
    {
        cout << cur->val << '\n';    //same for both preorder and inorder
        cur = cur->right;
    }
}



// post order
https://stackoverflow.com/questions/36384599/can-we-use-morris-traversal-for-postorder
/* 
concept  -> A simpler approach would be to do the symmetrically opposite of preorder morris traversal
and print the nodes in the reverse order. 
Root Ltree Rtree = preorder
Root Rtree Ltree => opp of preorder
Ltree Rtree Root => post order = reverse of (opp of preorder)
*/

//pre order
https://www.geeksforgeeks.org/morris-traversal-for-preorder/



//inorder dfs using stack
class Solution {
public:
    void dfs(TreeNode* root, int k) {
        stack<TreeNode*> s;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            
            root = s.top();
            s.pop();
            
            cout << root->val << endl;
            root = root->right;
        }
    }
};
