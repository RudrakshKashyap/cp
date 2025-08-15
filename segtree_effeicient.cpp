//safest bet
void build(int pos)
{
    while (pos > 1) {
        pos >>= 1;  // Move to parent

        // Push lazy values to children before merging
        if (lazy[pos] != lazy_neutral) {
            applyNode(pos << 1, lazy[pos]);
            applyNode((pos << 1) + 1, lazy[pos]);
            lazy[pos] = lazy_neutral;
        }
        tree[pos] = merge(tree[pos << 1], tree[(pos << 1) + 1]);
    }
}

//less safer
void build(int pos)
{
    while (pos > 1) {
        pos >>= 1;  // Move to parent

        if (lazy[pos] == lazy_neutral) tree[pos] = merge(tree[pos << 1], tree[(pos << 1) + 1]);
        else tree[pos] = apply(0/neutral, value, len[pos]);
    }
}

/*
we call build after push, 
if there are any lazy present that's only bc of the last change
and this node is already containing updated value
if lazy not present that means this node's children could have updated and 
this node can contain stale value, so we need to recalculate it
*/
void build(int pos)
{
    while (pos > 1) {
        pos >>= 1;  // Move to parent

        if (lazy[pos] == lazy_neutral) tree[pos] = merge(tree[pos << 1], tree[(pos << 1) + 1]);
    }
}


template <typename T, typename MergeOp, typename ApplyOp, typename LazyMergeOp>
class IterativeSegmentTree
{
private:
    int tree_size;          // Number of elements in the array
    int h;                  // Height of the tree
    vector<T> tree;         // Main tree storage
    vector<T> lazy;         // Lazy propagation values (lazy is already applied to cur node, it is only for children)
    vector<int> len;        // Length of each node's segment
    MergeOp merge;          // Merge operation for queries
    ApplyOp apply;          // Apply operation for updates
    LazyMergeOp lazy_merge; // Merge operation for lazy values
    T lazy_neutral;         // Neutral element for lazy updates


    void applyNode(int pos, T value)
    {
        tree[pos] = apply(tree[pos], value, len[pos]);
        if (pos < tree_size) lazy[pos] = lazy_merge(lazy[pos], value);
    }

    void push(int pos)
    {
        for (int s = h; s > 0; --s)
        {
            int i = pos >> s;
            if (lazy[i] != lazy_neutral)
            {
                applyNode(i << 1, lazy[i]);
                applyNode((i << 1) + 1, lazy[i]);
                lazy[i] = lazy_neutral;
            }
        }
    }

    //choose safe version from above
    void build(int pos)
    {
        while (pos > 1) {
            pos >>= 1;  // Move to parent
    
            if (lazy[pos] == lazy_neutral) tree[pos] = merge(tree[pos << 1], tree[(pos << 1) + 1]);
        }
    }


public:
    IterativeSegmentTree(
        vector<T> nums,
        MergeOp merge_op,
        ApplyOp apply_op,
        LazyMergeOp lazy_merge_op,
        T ln) : merge(merge_op),
                apply(apply_op),
                lazy_merge(lazy_merge_op),
                lazy_neutral(ln)
    {
        tree_size = nums.size();
        h = log2(tree_size);
        tree.resize(2 * tree_size);
        lazy.resize(tree_size, lazy_neutral);
        len.resize(2 * tree_size, 1);

        // Initialize leaves
        for (int i = 0; i < tree_size; ++i)
            tree[tree_size + i] = nums[i];
        for (int i = tree_size; i < 2 * tree_size; ++i)
            len[i] = 1;

        // Build internal nodes
        for (int i = tree_size - 1; i > 0; --i)
        {
            tree[i] = merge(tree[i << 1], tree[(i << 1) + 1]);
            len[i] = len[i << 1] + len[(i << 1) + 1];
        }
    }

    void rangeUpdate(int l, int r, T value)
    {
        l += tree_size;
        r += tree_size;
        int l0 = l, r0 = r;
        push(l0);
        push(r0);

        while (l <= r)
        {
            if (l % 2 == 1)
                applyNode(l++, value);
            if (r % 2 == 0)
                applyNode(r--, value);
            l >>= 1;
            r >>= 1;
        }

        build(l0);
        build(r0);
    }

    T rangeQuery(int l, int r)
    {
        l += tree_size;
        r += tree_size;
        push(l);
        push(r);

        T res = tree[l++]; // Initialize with first valid node
        while (l <= r)
        {
            if (l % 2 == 1) // Right child is completely in range
                res = merge(res, tree[l++]);
            if (r % 2 == 0) // Left child is completely in range
                res = merge(res, tree[r--]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }

    void pointUpdate(int pos, T value)
    {
        pos += tree_size;
        push(pos);
        tree[pos] = value;
        build(pos);
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    auto min_merge = [](ll a, ll b) { return min(a, b); };

    auto add_apply = [](ll current, ll update, int len) { return current + update ; };

    auto add_lazy_merge = [](ll a, ll b) { return a + b; };

    auto min_lazy_merge = [](int a, int b) { return b; }; // Last update wins


    IterativeSegmentTree<ll, decltype(min_merge), decltype(add_apply), decltype(add_lazy_merge)>
        st(nums, min_merge, add_apply, add_lazy_merge, 0);



    return 0;
}
