watch https://www.youtube.com/watch?v=GiN3jRdgxU4 from 28:10
2nd time when this edge become critical(backward flow 1) then when we reach node 2, we cant't go to node 1 because node
1 was already visited bc its dist is 2 from s and node 2 dist is 3 from s
				  |--- this edge is critical
				  V
	s----o-----1-----2-----o-----t
	 \			 \ /		   /
	   \ 		 / \		 /
	   	 o-----o     o-----o
	
all the implementation below are nice
https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
https://cp-algorithms.com/graph/edmonds_karp.html
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
