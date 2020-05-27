VI g[27];
bool v[27];
bool restack[27];

int getid(char c)
{
    if(c==' ') return 0;
    return c-'a'+1;
}

bool iscyclic(int cur)
{
    if(!v[cur])
    {
        v[cur]=true;
        restack[cur]=true;
        for(auto c: g[cur])
        {
            if(!v[c] && iscyclic(c)) return true;
            else if(restack[c]) return true;
        }
    }
    restack[cur]=false;
    return false;
}

void topsort(int cur,stack<int>& stack)
{
    v[cur]=true;
    for(auto c: g[cur])
        if(!v[c]) topsort(c,stack);

    stack.push(cur);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    string s[n];
    rep(i,n) cin>>s[i],s[i]+=" ";
    repa(i,1,27) g[0].eb(i);
    rep(i,n-1)
    {
        int pos=0;
        while(s[i][pos]==s[i+1][pos]) pos++;
        g[getid(s[i][pos])].eb(getid(s[i+1][pos]));
    }
    MS0(v);
    MS0(restack);
    int cyclic=0;
    rep(i,27) if(iscyclic(i)) cyclic=1;     //cycle detection
    if(cyclic) cout<<"Impossible"<<'\n';
    else
    {
        stack<int> ans;
        MS0(v);
        rep(i,27) if(!v[i]) topsort(i,ans);     //topsorting
        while(!ans.empty())
        {
            int i=ans.top();
            if(i>0) cout<<(char)(i+'a'-1);
            ans.pop();
        }
        cout<<'\n';
    }

    return 0;
}
