binary lifting

const int maxn = 1e5 + 5;
int f[maxn][logN], depth[maxn];
const int logN = 20;

//this code for dfs is only for tree, you should use bool visited array for graph
void dfs(int v, int par, int d)
{
    depth[v]=d;
    for (int i = 1; i < logN; i++)
        p[v][i] = p[p[v][i - 1]][i - 1];
    for(int c: g[v])
        if(c != par) {
            p[c][0] = v;
            dfs(c,v,d+1);
        }
}
int LCA (int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int i = logN - 1; i >= 0; i--)
        if (depth[p[u][i]] >= depth[v]) {
            u = p[u][i];
        }
    // int d = depth[u]-depth[v];
    // while(d>0)
    // {
    //     int i=log2(d);
    //     u=p[u][i];
    //     d -= (1<<i);
    // }

    if (u == v) return u;

    for (int i = logN - 1; i >= 0; i--)
        if (p[u][i] != p[v][i]) {
            u = p[u][i];
            v = p[v][i];
        }
    // while(p[u][0]!=p[v][0])
    // {
    //     u=p[u][0];
    //     v=p[v][0];
    // }

    return p[u][0];
}
