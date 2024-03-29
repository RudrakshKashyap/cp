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
            cout << cur->val << '\n';

            pre->right = nullptr;
            cur = cur->right;
        }
        else
        {
            pre->right = cur;
            cur = cur->left;
        }
    }
    else
    {
        cout << cur->val << '\n';

        cur = cur->right;
    }
}



// post order
https://stackoverflow.com/questions/36384599/can-we-use-morris-traversal-for-postorder

//pre order
https://www.geeksforgeeks.org/morris-traversal-for-preorder/
