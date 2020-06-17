watch https://www.youtube.com/watch?v=GiN3jRdgxU4 from 28:10 for time complexity.....i got the intuition but not exectly
how that time complexity came

2nd time when this edge become critical(backward flow 1) then when we reach node 2, we cant't go to node 1 because node
1 was already visited bc its dist is 2 from s and node 2 dist is 3 from s.
				  |--- this edge is critical
				  V
    s----o-----1-----2-----o-----t
     \           \ /           /
       \         / \         /
         o-----o     o-----o
	
all the implementation below are nice
https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
https://cp-algorithms.com/graph/edmonds_karp.html
in above implementations --- add both forward and backward edges to graph,initialize cap array=0 and only add forward capacity;

https://paste.ubuntu.com/7194906/
When BFS is used, the worst case time complexity can be reduced to O(VE2).
The above implementations uses adjacency matrix representation(array representation of graph)
though where BFS takes O(V2) time,
the time complexity of the above implementation is O(EV3)
#include <bits/stdc++.h>

using namespace std;

long long MF;
long long f[1000][1000];
long long c[1000][1000];
int timer;
int p[10000];

int n, m;

int used[1000];

const int inf = (int)(1e9);

int s, t;

bool bfs (int v, int t) {
	queue <int> q;
	q.push (v);

	while (!q.empty ()) {
		int x = q.front();
		q.pop();
		if (x == t)
			return true;
		for (int i = 1; i <= n; i++) {
			if (used[i] != timer && c[x][i] > f[x][i]) {
				p[i] = x;
				used[i] = timer;
				q.push (i);
			}
		}
	}

	return false;
}

int main () {
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w;
		c[x][y] = w;
	}
	
	s = 1;
	t = n;

	int x = inf;
	timer++;
	while (bfs (s, t)) {
		timer++;
		long long mn = inf;
		for (int i = t; i != s; i = p[i])
			mn = min (mn, c[p[i]][i] - f[p[i]][i]);
		
		for (int i = t; i != s; i = p[i])
			f[p[i]][i] += mn,
			f[i][p[i]] -= mn;
		
		MF += mn;
		memset (p, 0, sizeof p);
	}
	cout << MF;

	return 0;
}



https://codeforces.com/contest/498/submission/9251288 --- dinic
https://codeforces.com/contest/498/submission/9245747
typedef int F;
#define F_INF (1<<29)
#define MAXV 1000
#define MAXE 1000 // E*2!
 
F cap[MAXE],flow[MAXE];
int to[MAXE],_prev[MAXE],last[MAXV],used[MAXV],level[MAXV];
 
struct MaxFlow{
    int V,E;
 
    MaxFlow(int n){
        int i;
        V = n; E = 0;
        REP(i,V) last[i] = -1;
    }
 
    void add_edge(int x, int y, F f){
        cap[E] = f; flow[E] = 0; to[E] = y; _prev[E] = last[x]; last[x] = E; E++;
        cap[E] = 0; flow[E] = 0; to[E] = x; _prev[E] = last[y]; last[y] = E; E++;
    }
 
    bool bfs(int s, int t){
        int i;
        REP(i,V) level[i] = -1;
        queue <int> q;
        q.push(s); level[s] = 0;
        while(!q.empty()){
            int x = q.front(); q.pop();
            for(i=last[x];i>=0;i=_prev[i]) if(level[to[i]] == -1 && cap[i] > flow[i]) {q.push(to[i]); level[to[i]] = level[x] + 1;}
        }
        return (level[t] != -1);
    }
 
    F dfs(int v, int t, F f){
        int i;
        if(v == t) return f;
        for(i=used[v];i>=0;used[v]=i=_prev[i]) if(level[to[i]] > level[v] && cap[i] > flow[i]){
            F tmp = dfs(to[i],t,min(f,cap[i]-flow[i]));
            if(tmp > 0) {flow[i] += tmp; flow[i^1] -= tmp; return tmp;}
        }
        return 0;
    }
 
    F maxflow(int s, int t){
        int i;
        while(bfs(s,t)){
            REP(i,V) used[i] = last[i];
            while(dfs(s,t,F_INF) != 0);
        }
        F ans = 0;
        for(i=last[s];i>=0;i=_prev[i]) ans += flow[i];
        return ans;
    }
 
};
