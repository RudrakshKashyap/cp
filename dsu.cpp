int T[35];
int fi(int nod){
    if(!T[nod]){
        return nod;
    }
    return T[nod] = fi(T[nod]);
}
bool u(int x,int y){
    x = fi(x);
    y = fi(y);
    if(x == y){
        return 0;
    }
    T[x] = y;
    return 1;
}

int T[35];
int fi(int nod){
    if(nod==T[nod]){
        return nod;
    }
    return T[nod] = fi(T[nod]);
}
rep(i,n+1) T[i]=i;
rep(i,m)
{
    int x,y;
    cin>>x>>y;
    int p=fi(x),q=fi(y);
    T[p]=q;
}


int dsu[maxn]; //initialize with -1
int components = n;
int find(int x)
{
    // When dsu[x] < 0, x is a root and -dsu[x] is its tree size. When dsu[x] >= 0, dsu[x] is x's parent.
    return dsu[x] < 0 ? x : dsu[x] = find(dsu[x]);
}
int get_size(int x)
{
    return -dsu[find(x)];
}
bool join(int x, int y)
{
    int p = find(x), q = find(y);
    if(p == q) return 0;
    if (-dsu[p] < -dsu[q]) swap(p, q);
    dsu[p] += dsu[q];  //merging small set into bigger set
    dsu[q] = p; //making p as q's parent
    //components--;
    return 1;
}
