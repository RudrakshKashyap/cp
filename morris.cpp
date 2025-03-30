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


    /* Example Tree:
            1
           / \
          2   3
         / \
        4   5
    */
//inorder dfs using stack
void inorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while (curr != nullptr || !st.empty()) {
        // Reach the leftmost node
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        // Current node is nullptr, pop from stack
        curr = st.top();
        st.pop();
        
        cout << curr->val << " "; // Process the node (print, store, etc.)

        // Move to the right subtree
        curr = curr->right;
    }
}

void preorderTraversal(TreeNode* root) {
    if (!root) return;  // Edge case: empty tree

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();
        
        cout << curr->val << " ";  // Process the node

        // Push right first, then left (so left is processed next)
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}
