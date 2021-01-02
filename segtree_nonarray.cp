const int maxN = 300001;
int A[maxN];

struct node
{
    int l,r;
    ll evmax,evmin,odmax,odmin;
    struct node *left;
    struct node *right;
};

struct node* newNode(int l, int r)
{
    struct node* n = new struct node();
    n->l = l; n->r = r;
    if(l == r)
    {
        n->evmax = 0L; n->evmin = 0L; n->odmax = A[l]; n->odmin = A[l];
        n->left = nullptr; n->right = nullptr;
    }
    else
    {
        int mid = (l+r)/2;
        n->left = newNode(l, mid);
        n->right = newNode(mid+1, r);
        n->evmax = max(n->left->evmax + n->right->evmax, n->left->odmax - n->right->odmin);
        n->evmin = min(n->left->evmin + n->right->evmin, n->left->odmin - n->right->odmax);
        n->odmax = max(n->left->evmax + n->right->odmax, n->left->odmax - n->right->evmin);
        n->odmin = min(n->left->evmin + n->right->odmin, n->left->odmin - n->right->evmax);
    }
    return n;
}

void update(node* n, int i, int val)
{
    if(n->l == n->r)
    {
        n->evmax = 0L; n->evmin = 0L; n->odmax = val; n->odmin = val;
    }
    else
    {
        node* left = n->left;
        node* right = n->right;
        int mid = (n->l + n->r)/2;

        if(i <= mid) update(left, i, val);
        else  update(right, i, val);

        n->evmax = max(left->evmax + right->evmax, left->odmax - right->odmin);
        n->evmin = min(left->evmin + right->evmin, left->odmin - right->odmax);
        n->odmax = max(left->evmax + right->odmax, left->odmax - right->evmin);
        n->odmin = min(left->evmin + right->odmin, left->odmin - right->evmax);
    }
}

ll query(node* n, int l, int r)
{
    if(r < n->l || n->r < l) return 0;
    if(l <= n->l && n->r <= r) return n->freq;

    node* left = n->left;
    node* right = n->right;

    ll p1 = query(left, l, r);
    ll p2 = query(right, l, r);
    return (p1+p2);
}

node* root = newNode(0, n-1);
print(root->odmax);
update(root,idx, val); //update(root,l,A[r]);
