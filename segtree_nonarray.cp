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

///////////////////////////////////
const int maxn = 1e9 + 2;
 
struct node
{
    ll val, lazy;
    struct node *left;
    struct node *right;
    node() : val(0), lazy(0), left(NULL), right(NULL){};
};
 
void update(node* n, int start, int end, int l, int r, int val)
{
    if(r < start or end < l) return;
    if(l <= start and end <= r)
    {
        n->val += val;
        return;
    }
    int mid = (start + end)/2;
    ll p1 = 0, p2 = 0;
    if(r <= mid)
    {
        if(n->left == NULL) n->left = new node();
        update(n->left, start, mid, l, r, val);
    }
    else if(mid < l)
    {
        if(n->right == NULL) n->right = new node();
        update(n->right, mid+1, end, l, r, val);
    }
    else
    {
        if(n->left == NULL) n->left = new node();
        update(n->left, start, mid, l, r, val);
        if(n->right == NULL) n->right = new node();
        update(n->right, mid+1, end, l, r, val);
    }
    if(n->left) p1 = n->left->val;
    if(n->right) p2 = n->right->val;
    n->val = p1 + p2;
    return;
}
 
ll query(node* n, int start, int end, int l, int r)
{   
    if(n == NULL or r < start or end < l) return 0;
    
    if(n->lazy != 0)
    {
        ll dx = n->lazy;
        n->lazy = 0;
		n->val += dx * (end - start + 1);
        // n->val += dx;
 
		if(start != end)
        {
            if(n->left == NULL) n->left = new node();
            if(n->right == NULL) n->right = new node();
            n->left->lazy += dx, n->right->lazy += dx;
        }
    }
    if(l <= start and end <= r) return n->val;
    int mid = (start + end)/2;
    ll p1 = query(n->left, start, mid, l, r);
    ll p2 = query(n->right, mid+1, end, l, r);
    return p1+p2;
}

/*with lazy update*/
void update(node* n, int start, int end, int l, int r, int val)
{
    if(n->lazy != 0)
    {
        ll dx = n->lazy;
        n->lazy = 0;
		n->val += dx * (end - start + 1);
        // n->val += dx;
 
		if(start != end)
        {
            if(n->left == NULL) n->left = new node();
            if(n->right == NULL) n->right = new node();
            n->left->lazy += dx, n->right->lazy += dx;
        }
    }
 
    if(r < start or end < l) return;
    if(l <= start and end <= r)
    {
        n->val += val;
        if(start != end)
        {
            if(n->left == NULL) n->left = new node();
            if(n->right == NULL) n->right = new node();
            n->left->lazy += val;
            n->right->lazy += val;
        }
        return;
    }
 
    int mid = (start + end)/2;
    ll p1 = 0, p2 = 0; //initialize with 1e9 if returning min
    if(r <= mid)
    {
        if(n->left == NULL) n->left = new node();
        update(n->left, start, mid, l, r, val);
    }
    else if(mid < l)
    {
        if(n->right == NULL) n->right = new node();
        update(n->right, mid+1, end, l, r, val);
    }
    else
    {
        if(n->left == NULL) n->left = new node();
        update(n->left, start, mid, l, r, val);
        if(n->right == NULL) n->right = new node();
        update(n->right, mid+1, end, l, r, val);
    }
    if(n->left) p1 = n->left->val;
    if(n->right) p2 = n->right->val;
    n->val = p1 + p2;
    return;
}
