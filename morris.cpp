//inorder    left root right

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
