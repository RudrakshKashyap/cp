//tarjan's algo , https://www.youtube.com/watch?v=qrAub5z8FeA

## [Connected Components](https://cp-algorithms.com/graph/search-for-connected-components.html#implementation)
Simple DFS

## Finding Bridges DFS in $O(N + M)$

```cpp
int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to: adj[v]) {
        if (to == p) continue;
        if (!visited[to]) dfs(to, v);

        //lowest time that we can reach form v
        low[v] = min(low[v], low[to]);

        //cutting this edge will break the graph
        if (low[to] > tin[v])
            IS_BRIDGE(v, to);
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}
```

## [Finding Bridges Offline](https://cp-algorithms.com/graph/bridge-searching-online.html) - TODO