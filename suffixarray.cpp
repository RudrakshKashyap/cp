https://leetcode.com/problems/longest-duplicate-substring/discuss/695143/C%2B%2Bsuffix-array(100-efficient)
https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/

void radix_sort(vector<pair<pair<int,int>,int>>& a) //just counting sort on both element of pairs
{
    //sort according to second element
    {
        int n=a.size();
        vector<int> cnt(n);
        for(auto x: a) cnt[x.first.second]++;
        vector<pair<pair<int,int>,int>> a_new(n);
        vector<int> pos(n);
        pos[0]=0;
        for(int i=1;i<n;i++) pos[i] = pos[i-1] + cnt[i-1];  //starting position of number
        for(auto x: a)  //filling number to their corrosponding position
        {
            int i = x.first.second;
            a_new[pos[i]]=x;
            pos[i]++;
        }
        a = a_new;
    }

    //sorting according to first element
    {
        int n=a.size();
        vector<int> cnt(n);
        for(auto x: a) cnt[x.first.first]++;
        vector<pair<pair<int,int>,int>> a_new(n);
        vector<int> pos(n);
        pos[0]=0;
        for(int i=1;i<n;i++) pos[i] = pos[i-1] + cnt[i-1];  //starting position of number
        for(auto x: a)  //filling number to their corrosponding position
        {
            int i = x.first.first;
            a_new[pos[i]]=x;
            pos[i]++;
        }
        a = a_new;
    }
}


vector<int> sa(string s)
{
    s+="$";
    int n = s.size();
    vector<int> p(n), c(n);
    {
        // k = 0
        vector<pair<char,int>> a(n);
        for(int i=0;i<n;i++) a[i] = {s[i], i};
        sort(a.begin(),a.end());

        for(int i=0;i<n;i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for(int i=1;i<n;i++)
        {
            if(a[i].first  == a[i-1].first) c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]] + 1;
        }
    }

    for(int k=0; (1<<k) < n; k++)
    {
        // k -> k+1
        vector<pair<pair<int,int>,int>> a(n);
        for(int i=0;i<n;i++) a[i] = {{c[i],c[(i + (1<<k))%n]},i};   //making pairs
        sort(a.begin(),a.end());    //radix_sort(a);
        for(int i=0;i<n;i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for(int i=1;i<n;i++)
        {
            if(a[i].first  == a[i-1].first) c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]] + 1;
        }
    }

    // for(int i=0;i<n;i++) cout<<p[i]<<' ';

    return p;
}
