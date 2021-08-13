vector<int> entr, ext;
    
    int timer = 0;
    void dfs(int u, int prev)
    {
        entr[u] = timer++;
        for(const int& v : adj[u])
            if(v != prev)
                dfs(v,u);
        ext[u] = timer++;
    }

vector<LL> flattenedTree(2*n);
for(int u = 0; u < n; u++)
{
    flattenedTree[entr[u]] = s[u];
    flattenedTree[ext[u]] = -s[u]; 
}
