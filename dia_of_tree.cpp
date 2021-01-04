//https://codeforces.com/contest/1294/problem/F

int n;
const int maxn = 2e5;
VI g[maxn];
int par[maxn];


PI dfs(int v, int p = -1, int d = 0)    //return max distance and starting vertex
{
    par[v] = p;
    PI res = {d, v};
    for(auto c : g[v])
    {
        if(c == p) continue;
        res = max(res, dfs(c, v, d+1));
    }
    return res;
}

int main()
{
	
	cin >> n;
    rep(i, n-1)
    {
        int x, y;
        cin >> x >> y;
        x--;y--;
        g[x].eb(y);
        g[y].eb(x);
    }

    PI da = dfs(0); //first end point of diam
    PI db = dfs(da.S);

    VI diam;
    int v = db.S;
    while(v != da.S)
    {
        diam.eb(v);
        v = par[v];
    }
    diam.eb(v);
	
	return 0;
}

/////////////////////////////////////////////////////

const int maxn = 2e5;
VI g[maxn];
int far, far_dist, dist[maxn];

void dfs(int u, int p, int d)
{
    amax(dist[u], d);
    if(amax(far_dist, d)) far = u;  //calculating farthest node form root
    for(int v : g[u])
    {
        if(v == p) continue;
        dfs(v, u, d+1);
    }
}

    int n;
    cin >> n;
    rep(i,n-1)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].eb(b);
        g[b].eb(a);
    }
    dfs(0, -1, 0);
    dfs(far, -1, 0); //fartherst node or first end point of diam
    dfs(far, -1, 0); //2nd end point of diam
    cout << far_dist << ' ';
    // rep(i, n) cout << dist[i] << ' ';
