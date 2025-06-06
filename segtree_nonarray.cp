struct node
{
    ll val, lazy;
    struct node *left;
    struct node *right;
    node() : val(0), lazy(0), left(NULL), right(NULL){};
};
 
void update(node* n, int start, int end, int l, int r, int val)
{   
    if(n->left == NULL) n->left = new node();
    if(n->right == NULL) n->right = new node();
 
//     if(n->lazy != 0)
//     {
//         ll dx = n->lazy;
//         n->lazy = 0;
//         n->val += dx * (end - start + 1);
//         if(start != end) n->left->lazy += dx, n->right->lazy += dx;
//     }

    //this line should be only after lazy update, bc lazy has to be applied to current node as well
    //that means if child have lazy, it should be applied first before calculating current node value again
    if(r < start or end < l) return; 
 
    if(l <= start and end <= r)
    {
        n->val += val * (end - start + 1);
//         if(start != end) n->left->lazy += val, n->right->lazy += val;
        return;
    }
 
    int mid = (start + end)/2;
    update(n->left, start, mid, l, r, val);
    update(n->right, mid+1, end, l, r, val);
    n->val = n->left->val + n->right->val;
    return;
}
 
ll query(node* n, int start, int end, int l, int r)
{
       if(n == NULL or r < start or end < l) return 0;
 
//     if(n->lazy != 0)
//     {
//         ll dx = n->lazy;
//         n->lazy = 0;
//         n->val += dx * (end - start + 1);
 
//         if(start != end) n->left->lazy += dx, n->right->lazy += dx;
//     }

 
    if(l <= start and end <= r) return n->val;
    int mid = (start + end)/2;
    ll p1 = query(n->left, start, mid, l, r);
    ll p2 = query(n->right, mid+1, end, l, r);
    return p1 + p2;
}

node* root = new node();
update(root,....)
