//https://www.youtube.com/watch?v=09_LlHjoEiY --. all graph algos

	4			5 			6	  		7
	 
	 	2(dist = '2')		3(dist = '1')

					1
	
	2 is connected to node 4,5,6,7 with edge weight 1
	3 is also connected to node 4,5,6,7 with edge weight 100
	
	queue<dist, vertex>, distance represented with '' marks
	1) we pop 1 from queue and push {'1', 3} and push {'2', 2}
	2) we now pop vertex 3 and dilute distance to node 4,5,6,7 with 101 and push {'101', 4},{'101', 5},{'101', 6},{'101', 7} into queue
	3) we pop vertex 2 and again dilute the distance to node 4,5,6,7 and push {'3', 4}, {'3', 5}, {'3', 6}, {'3', 7} to queue
	
	we notice that we now have useless copy of {'101', 4}... in our queue, and when we pop it we will again itreate over neighbours of 4
	to dilute them, which are already diluted by {'3', 4}



const int maxn = 5e5;
vector<PI> g[maxn]; // vertex weight
ll d[maxn];
int p[maxn];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    rep(i, m)
    {
        int x, y, w;
        cin >> x >> y >> w;
        g[x].eb(y, w);
        // g[y].eb(x, w);
    }

    fill(&d[0], &d[0] + sizeof(d)/sizeof(ll), 1e18);
    MS1(p);
    minpq<pair<ll, int>> q; // dist vertex
    q.push({d[s] = 0, s});
    while(!q.empty())
    {
        int v = q.top().S;
        ll d_v = q.top().F;
        q.pop();
        if(d_v != d[v]) continue; // to prevent duplicates

        for(auto [to, wei] : g[v])
        {
            if(d[v] + (ll) wei < d[to]) // wei is int but adding it to long long
            {
                d[to] = d[v] + wei;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }

    if(d[t] == 1e18) print(-1);
    else
    {
        VI path;
        path.eb(t);
        int x = t;	//below we have to print d[t]
        while(p[x] != s)
		{
            path.eb(p[x]);
            x = p[x];
        }
        path.eb(s);
        reverse(all(path));
        cout << d[t] << ' ' << SZ(path)-1<<'\n';
        rep(i, SZ(path)-1) print(path[i], path[i+1]);
    }

    return 0;
}
