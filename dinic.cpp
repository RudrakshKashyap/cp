//https://codeforces.com/contest/1624/submission/142198189

const int INF = int(1e9) + 5;
 
struct dinic_matching {
    int n, m;
    vector<vector<int>> adj;
    vector<int> dist;
    vector<bool> matched;
    vector<int> edge_index;
    vector<int> prv;
 
    dinic_matching() {
        init(0, 0);
    }
 
    dinic_matching(int _n, int _m) {
        init(_n, _m);
    }
 
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        adj.assign(n, {});
        dist.resize(n);
        matched.resize(n);
        edge_index.resize(n);
        prv.resize(m);
    }
 
    void add_edge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < m);
        adj[a].push_back(b);
    }
 
    void bfs_check(queue<int> &q, int left, int new_dist) {
        if (new_dist < dist[left]) {
            dist[left] = new_dist;
            q.push(left);
        }
    }
 
    bool bfs() {
        dist.assign(n, INF);
        queue<int> q;
 
        for (int i = 0; i < n; i++)
            if (!matched[i])
                bfs_check(q, i, 0);
 
        bool has_path = false;
 
        while (!q.empty()) {
            int left = q.front(); q.pop();
 
            for (int right : adj[left])
                if (prv[right] < 0)
                    has_path = true;
                else
                    bfs_check(q, prv[right], dist[left] + 1);
        }
 
        return has_path;
    }
 
    bool dfs(int left) {
        // Because we are only performing DFS in increasing order of dist, we don't have to revisit fully searched edges
        // again later.
        while (edge_index[left] < int(adj[left].size())) {
            int right = adj[left][edge_index[left]++];
            bool solved = false;
 
            if (prv[right] < 0 || (dist[left] + 1 == dist[prv[right]] && dfs(prv[right]))) {
                prv[right] = left;
                matched[left] = true;
                solved = true;
            }
 
            if (solved)
                return true;
        }
 
        dist[left] = INF;
        return false;
    }
 
    int match() {
        matched.assign(n, false);
        prv.assign(m, -1);
        int matches = 0;
 
        while (bfs()) {
            edge_index.assign(n, 0);
 
            for (int i = 0; i < n; i++)
                if (!matched[i] && dfs(i))
                    matches++;
        }
 
        return matches;
    }
 
    vector<bool> reachable_left, reachable_right;
 
    void reachable_dfs(int left) {
        reachable_left[left] = true;
 
        for (int right : adj[left])
            if (prv[right] != left && !reachable_right[right]) {
                reachable_right[right] = true;
                int next_left = prv[right];
 
                if (next_left >= 0 && !reachable_left[next_left])
                    reachable_dfs(next_left);
            }
    }
 
    // The min vertex cover in a bipartite graph corresponds to the min cut in its flow graph.
    vector<int> min_vertex_cover() {
        int match_size = match();
        reachable_left.assign(n, false);
        reachable_right.assign(m, false);
 
        for (int i = 0; i < n; i++)
            if (!matched[i] && !reachable_left[i])
                reachable_dfs(i);
 
        vector<int> cover;
 
        for (int i = 0; i < n; i++)
            if (!reachable_left[i])
                cover.push_back(i);
 
        for (int i = 0; i < m; i++)
            if (reachable_right[i])
                cover.push_back(n + i);
 
        assert(int(cover.size()) == match_size);
        return cover;
    }
 
    // The max independent set is the complement of the min vertex cover.
    vector<int> max_independent_set() {
        int cover_size = int(min_vertex_cover().size());
        vector<int> independent_set;
 
        for (int i = 0; i < n; i++)
            if (reachable_left[i])
                independent_set.push_back(i);
 
        for (int i = 0; i < m; i++)
            if (!reachable_right[i])
                independent_set.push_back(n + i);
 
        assert(int(independent_set.size()) + cover_size == n + m);
        return independent_set;
    }
};
 
 
void run_case() {
    int N;
    cin >> N;
    vector<int> A(N);
 
    for (auto &a : A)
        cin >> a;
 
    dinic_matching graph(N, N);
 
    for (int i = 0; i < N; i++) {
        int a = A[i];
 
        while (a > 0) {
            if (a <= N)
                graph.add_edge(i, a - 1);
 
            a /= 2;
        }
    }
 
    cout << (graph.match() == N ? "YES" : "NO") << '\n';
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
