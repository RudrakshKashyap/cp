//eulerian path
VI g[maxn],circuit;

void dfs(int i)
{
    while(!g[i].empty())
    {
        int v=g[i].back();
        g[i].pop_back();
        dfs(v);
    }
    circuit.eb(i);
}

dfs(root);
reverse(all(circuit));

//euler cycle
https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/ ---Hierholzer’s Algorithm
https://www.geeksforgeeks.org/fleurys-algorithm-for-printing-eulerian-path/ --fleury's algo


//////////////////////////////////////////////////
vector<PI> g[7];
int done[101];
stack<pair<int,char>> ans;
vector<pair<int,char>> aa;
 
void dfs(int i)
{
    for(auto c:g[i])
    {
        if(done[abs(c.S)]) continue;
        done[abs(c.S)]=1;
        dfs(c.F);
        ans.push({abs(c.S),(c.S>0) ? '+':'-'});
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    MS0(done);
    int n;
    cin>>n;
    rep(i,n)
    {
        int u,v;
        cin>>u>>v;
        g[u].pb({v,i+1});
        g[v].pb({u,-(i+1)});
    }
    int v1=-1,v2=-1;
    rep(i,7)
    {
        if(SZ(g[i])%2)
        {
            if(v1==-1) v1=i;
            else if(v2==-1) v2=i;
            else {cout<<"No solution";return 0;}
        }
    }
    if(v1!=-1 && v2==-1) {cout<<"No solution";return 0;}
    if(v1==-1)
    {
        rep(i,7) if(SZ(g[i])>0){v1=i;break;}
    }
    dfs(v1);
    if(SZ(ans)!=n){cout<<"No solution";return 0;}
    while(!ans.empty())
    {
        auto it=ans.top();
        cout<<it.F<<' '<<it.S<<'\n';
        ans.pop();
    }
 
    return 0;
}
