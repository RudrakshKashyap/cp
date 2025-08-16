# [LCA and RMQ](https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/)

```
Let LCA(u, v, w) be the LCA of v and w with respect to root u. 
To compute LCA(u, v, w), we can compute, for any fixed r,
LCA(r, u, v)
LCA(r, u, w)
LCA(r, v, w)
and take the "odd man out", i.e., 
if two are equal and the third is different, then take the third,
else they're all equal, so take that node.

For Query(root, u, v):
Let a = LCA(u, v), b = LCA(root, u) and c = LCA(root, v)
and the answer for the query is the one value that is different from other two if all of them are not equal
if(a == b)return c;
else if(b == c)return a;
else if(c == a)return b;
else throw an error ; // condition no possible
```

# [Binary lifting](https://youtu.be/oib-XsjFa-M?t=331)

```cpp
/*
    u <----------------  v             root
    1------2------3------4------5------6
          2^0    2^1           2^2                  2^3
           1      2             4                   -1
*/
class TreeAncestor {
    int n, maxLog;
    vector<int> depth;
    vector<vector<int>> adj;
    vector<vector<int>> up; // up[u][i] = 2^i-th ancestor of u

    void dfs(int u, int parent) {
        up[u][0] = parent;
        for (int i = 1; i <= maxLog; i++) {
            if (up[u][i-1] != -1)
                up[u][i] = up[up[u][i-1]][i-1];
            else
                up[u][i] = -1;
        }

        for (int v : adj[u]) {
            if (v == parent) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

public:
    TreeAncestor(int n, vector<vector<int>>& edges) {
        this->n = n;
        maxLog = ceil(log2(n));
        depth.resize(n);
        adj.resize(n);
        up.assign(n, vector<int>(maxLog + 1, -1));

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        depth[0] = 0; // Root node
        dfs(0, -1);
    }

    int kthAncestor(int node, int k) {
        if (k > depth[node]) return -1;
        
        for (int i = 0; i <= maxLog; i++) {
            if (k & (1 << i)) {
                node = up[node][i];
                if (node == -1) break;
            }
        }
        return node;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];
        u = kthAncestor(u, diff);

        if (u == v) return v;

        for (int i = maxLog; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
};

int main() {
    // Example tree:
    //       0
    //     /   \
    //    1     2
    //   / \   / \
    //  3   4 5   6
    int n = 7;
    vector<vector<int>> edges = {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}};
    
    TreeAncestor ta(n, edges);
    
    // Test LCA
    cout << "LCA of 3 and 4: " << ta.lca(3, 4) << endl; // 1
    cout << "LCA of 5 and 6: " << ta.lca(5, 6) << endl; // 2
    cout << "LCA of 3 and 5: " << ta.lca(3, 5) << endl; // 0
    
    // Test Kth Ancestor
    cout << "1st ancestor of 3: " << ta.kthAncestor(3, 1) << endl; // 1
    cout << "2nd ancestor of 3: " << ta.kthAncestor(3, 2) << endl; // 0
    cout << "3rd ancestor of 3: " << ta.kthAncestor(3, 3) << endl; // -1
    
    return 0;
}
```
---

# Sparse Table - O(1) Queries

```cpp
class LCA {
    int n;
    vector<vector<int>> adj;
    vector<int> depth;
    vector<int> first_occurrence;
    vector<int> euler_tour;
    vector<vector<int>> sparse_table;
    vector<int> log_table;

    void dfs(int u, int parent, int dep) {
        depth[u] = dep;
        first_occurrence[u] = euler_tour.size();
        euler_tour.push_back(u);
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs(v, u, dep + 1);
            euler_tour.push_back(u);  // Backtrack to parent
        }
    }

    void build_sparse_table() {
        // atmost 2*n - 1, = 2*n - leafs, every leaf is counted only once
        int m = euler_tour.size();
        
        // Precompute logarithm values for queries
        log_table.resize(m + 1);
        log_table[1] = 0;
        for (int i = 2; i <= m; i++) {
            log_table[i] = log_table[i / 2] + 1;
        }
        
        int k = log_table[m] + 1;
        sparse_table = vector<vector<int>>(k, vector<int>(m));
        
        for (int i = 0; i < m; i++) {
            sparse_table[0][i] = euler_tour[i];
        }
        
        for (int i = 1; i < k; i++) {
            for (int j = 0; j + (1 << i) <= m; j++) {
                int left = sparse_table[i - 1][j];
                int right = sparse_table[i - 1][j + (1 << (i - 1))];
                sparse_table[i][j] = (depth[left] < depth[right]) ? left : right;
            }
        }
    }

public:
    LCA(int _n, vector<vector<int>>& edges) : n(_n), adj(_n), depth(_n) {
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        first_occurrence.resize(n);
        dfs(0, -1, 0);  // Root the tree at node 0
        build_sparse_table();
    }

    int lca(int u, int v) {
        int l = first_occurrence[u];
        int r = first_occurrence[v];
        if (l > r) swap(l, r);
        
        int len = r - l + 1;
        int k = log_table[len];
        
        int left_node = sparse_table[k][l];
        int right_node = sparse_table[k][r - (1 << k) + 1];
        
        return (depth[left_node] < depth[right_node]) ? left_node : right_node;
    }
};
```