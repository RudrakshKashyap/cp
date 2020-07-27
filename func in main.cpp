vector<bool> mark(Alp);
function<void(int)> dfs = [&](int u)
{
    mark[u] = true;
    for (auto v : adj[u])
        if (!mark[v])
            dfs(v);
};
