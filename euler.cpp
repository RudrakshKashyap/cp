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
