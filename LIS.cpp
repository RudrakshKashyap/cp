const int maxn=2e5;
int n;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n;
    VI v;
    rep(i,n)
    {
        int a;
        cin>>a;
        int p=lower_bound(v.begin(),v.end(),a)-v.begin(); //pos of a in vector
        if(p<SZ(v)) v[p]=a;
        else v.pb(a);
    }
    cout<<SZ(v);

    return 0;
}
