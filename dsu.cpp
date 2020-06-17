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
