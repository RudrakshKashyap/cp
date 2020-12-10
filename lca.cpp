binary lifting

const int maxn = 1e5 + 5;
const int logN = 20;
int p[maxn][logN], depth[maxn];

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



//---------sparse table

const int k = ;   //log2 floor of 2*maxn-1
const int maxn = 2e5;  //maxn

int n;  //size of arr
long long table[2*maxn - 1][k + 1]; // k + 1 because we need to access table[r][MAXLOG]
// 2*maxn because we need exactly 2*maxn - 1 elements to store euler tour
int numlog[2*maxn];
int dep[2*maxn-1];
int tim;
int tin[maxn];
VI euler;
VI g[maxn];

// building sparse table with depth array
void build()
{
    numlog[1] = 0;
    for (int i = 2; i <= n; i++)
        numlog[i] = numlog[i / 2] + 1;

    // build Sparse Table
    for(int i = 0; i < n; i++)
        table[i][0] = i;
    for(int j = 1; j <= numlog[n]; j++)
    {
        for(int i = 0; i <= n - (1 << j); i++)
        {
            if(dep[table[i][j - 1]] > dep[ table[i + (1 << (j - 1))][j - 1] ]) table[i][j] = table[i + (1 << (j - 1))][j - 1];
            else table[i][j] = table[i][j - 1];
        }
    }
}

int query(int l, int r)    //these l and r are inclusive [l,r]
{
    if(l == r) return l;
    int curlog = numlog[r - l + 1];
    return (dep[table[l][curlog]] > dep[ table[r - (1 << curlog) + 1][curlog] ]) ? table[r - (1 << curlog) + 1][curlog] : table[l][curlog];
}

void dfs(int v, int p, int d)
{
    tin[v] = tim;  //visiting node v at time tim or FAI
    dep[tim] = d;   //depth array corrosponding to the euler array
    euler.eb(v);
    tim++;
    for(auto c : g[v])
    {
        if(c != p)
        {
            dfs(c,v,d+1);
            euler.eb(v);
            dep[tim] = d;
            tim++;
        }
    }
}


int lca(int x, int y)
{
    if(x == y) return x;
    if(tin[x] > tin[y]) swap(x,y);
    return euler[query(tin[x],tin[y])];
}

Let LCA(u, v, w) be the LCA of v and w with respect to root u. To compute LCA(u, v, w), we can compute, for any fixed r,

LCA(r, u, v)
LCA(r, u, w)
LCA(r, v, w)
and take the "odd man out", i.e., if two are equal and the third is different, then take the third, else they're all equal, so take that node.

For Query(root,u,v):

Let a=LCA(u,v),b=LCA(root,u) and c=LCA(root,v)
and the answer for the query is the one value that is different from other two if all of them are not equal
if(a==b)return c;
else if(b==c)return a;
else if(c==a)return b;
else throw an error ; // condition no possible


