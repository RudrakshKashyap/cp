https://codeforces.com/blog/entry/12796?#comment-175287
https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/

// Below codes will give n+1 SA of n+1 indecies including $ sign----------------------------------------------

https://codeforces.com/edu/course/2
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




// above code optimised

void count_sort(vector<int>& p, vector<int>& c)
{
    //sort vector of indecies according to their ranks(or class)
    {
        int n=p.size();
        vector<int> cnt(n);
        for(auto x: p) cnt[x]++;
        vector<int> p_new(n);
        vector<int> pos(n);
        pos[0]=0;
        for(int i=1;i<n;i++) pos[i] = pos[i-1] + cnt[i-1];  //starting position of number
        for(auto x: p)  //filling number to their corrosponding position
        {
            int i = c[x];
            p_new[pos[i]]=x;
            pos[i]++;
        }
        p = p_new;
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
        for(int i=0;i<n;i++) p[i] = (p[i] - (1<<k) + n)%n;  //if we go back (1<<k) we will find that right part of our string is already sorted
        count_sort(p,c);    //we just need to perform counting sort only for left part

        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for(int i=1;i<n;i++)
        {
            pair<int,int> prev = {c[p[i-1]],c[(p[i-1] + (1<<k))%n]};
            pair<int,int> now = {c[p[i]],c[(p[i] + (1<<k))%n]};
            if(now == prev) c_new[p[i]] = c[p[i-1]];
            else c_new[p[i]] = c[p[i-1]] + 1;
        }
    }

    // for(int i=0;i<n;i++) cout<<p[i]<<' ';

    return p;
}


// kasai algo
Let's look at two adjacent suffixes in the sorted order (order of the suffix array). Let their starting positions be i and j and their lcp equal to k>0. If we remove the first letter of both suffixes - i.e. we take the suffixes i+1 and j+1 - then it should be obvious that the lcp of these two is k−1. However we cannot use this value and write it in the lcp array, because these two suffixes might not be next to each other in the sorted order. The suffix i+1 will of course be smaller than the suffix j+1, but there might be some suffixes between them. However, since we know that the LCP between two suffixes is the minimum value of all transitions, we also know that the LCP between any two pairs in that interval has to be at least k−1, especially also between i+1 and the next suffix. And possibly it can be bigger.


     
if suffix of index i comes before j in SA(and their lcp>0) 
then suffix of index i+1 will come before suffix of index j+1 because when we compared suffix of index i and j
we found that their first char is same(bc lcp>0) so ofcourse we have compared them with their next characters

suffix of index i+1
some other suffix --- will also have (k-1) char common
some other suffix
some other suffix
some other suffix
suffix of index j+1 --- this have k-1 char common

