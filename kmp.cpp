//pi function and kmp algo
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}


int kmp(string p, string t)
{
    int ans = 0;
    int M = SZ(p);
    int N = SZ(t);
    VI lps = prefix_function(p);
    int i = 0; //idx for txt
    int j = 0; //idx for pat
    while(i < N)
    {
        if(p[j] == t[i]) i++, j++;
        if(j == M) //found pat at idx i-j (1 based index)
        {
            j = lps[j-1];
            ans++;
        }
        else if(i < N && p[j] != t[i])
        {
            if(j == 0) i++;
            else j = lps[j-1];
        }
    }
    return ans;
}
