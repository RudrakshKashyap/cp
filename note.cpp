ctrl shift h for adding header not working lol
factor command on linux
oeis.org
https://www.desmos.com/
file-header/lib/templates i did this command mv C.tmpl C.tmpl_original


int a = std::numeric_limits<int>::max();

//it also works for array,vectors ,list etc
string s="123"
do {
	cout<<s<<'\n';
} while(next_permutation(s.begin(),s.end()));
//123
//132
//213
.. till //321 after that it will return false


strchr(str,'a'); used for finding occurrence of a character in a string.
str = to_string(a);
a = stoi(str);

vec.capacity(); vec.reserve(1000);

queue<int>qu; print(qu);


~(-1)=0
lower_bound(arr,arr+n,35)-arr;


return 1 if a<b;

// Compare 3 characters from 3rd position
// (or index 2) of str1 with 3 characters
// from 4th position of str2.
if (str1.compare(2, 3, str2, 3, 3) == 0)
   cout<<"Equal";
else
   cout<<"Not equal";



vector<int> g[100000];
int par[100000];
int depth[100000];

void dfs(int v, int p, int d)
{
    depth[v] = d;
    par[v] = p;
    for(int c: g[v])
        if(c != p) dfs(c, v, d + 1);
}
dfs(0, -1, 0);
vector<int> getpath(int a, int b)
{
    vector<int> ans, path1, path2;
    path1.push_back(a);
    path2.push_back(b);
    while(a != b)
    {
        if(depth[a] < depth[b]) path2.push_back(b = par[b]);
        else if(depth[a] > depth[b]) path1.push_back(a = par[a]);
        else if(depth[a] == depth[b]) path1.push_back(a = par[a]), path2.push_back(b = par[b]);
    }
    reverse(path2.begin(), path2.end());
    path2.erase(path2.begin());
    path1.insert(path1.end(), path2.begin(), path2.end());
    return ans = path1;
}






/*
#define PROD //clocking off

#ifndef PROD
clock_t stop_s,start_s;
start_s=clock();
#endif

#ifndef PROD
stop_s=clock();
cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
#endif

*/


// Using copy_n() to copy contents
    copy_n(ar, 6, ar1);

// Initailising starting value as 100
    int st = 100;

    std::iota(numbers, numbers + 10, st);
Elements are : 100 101 102 103 104 105 106 107 108 109

// A quick way to swap a and b
a ^= b;
b ^= a;
a ^= b;




/*
https://leetcode.com/problems/kth-largest-element-in-an-array/
*/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        long lw=INT_MIN;
        long hg=INT_MAX;
        while(lw<=hg)
        {
            long mid=(lw+hg)/2;
            int ct=0,e=0;
            for(auto i:nums)
            {
                if(i>mid)
                    ct++;
                else if(i==mid)
                    e++;
            }
            if(ct<k&&ct+e>=k)
            {
                return mid;
            }
            else if(ct+e<k)
            {
                hg=mid-1;
            }
            else
            {
                lw=mid+1;
            }

        }
        return 0;
    }
};
Number of Digtits in base b = 1 + floor( log b (N) )
Example :
In base 10 ,N=1430 ,
here number of digits=1+floor(3.15)=4

a std::map has a BidirectionalIterator. A BidirectionalIterator does not support random access and can only be incremented or decremented.



https://ideone.com/SMIZgR -- max xor pair

string s;
cin>>s; // Suppose s = "100100101"
int n = stoi(s, 0, 2);
cout<<n; // 293


https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/graphtheory/EulerianPathDirectedEdgesAdjacencyList.java
or see the code at the last of the file

 ffs() function: ffs() function returns the index of first least significant set bit.
int clz(int N) {
    return N ? 32 - __builtin_clz(N) : -inf;
}

lcm=a*b/__gcd(a,b);






int fib(int n) {
  double phi = (1 + sqrt(5)) / 2;
  return round(pow(phi, n) / sqrt(5));
}







https://codeforces.com/contest/723/problem/E

#include <bits/stdc++.h>

#define fc first
#define sc second
#define all(x) x.begin(), x.end()
#define pb push_back
#define popb pop_back
#define ll long long

using namespace std;

const int N = (int) 200 + 7;
int d[N];
int d_in[N], d_out[N];
multiset <int> g[N];
vector <pair <int, int> > go;

void dfs(int v) {
    while (g[v].size() > 0) {
        int to = *g[v].begin();
        go.pb({v, to});
        g[to].erase(g[to].find(v));
        g[v].erase(g[v].begin());
        dfs(to);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(d, 0, sizeof d);
        memset(d_in, 0, sizeof d_in);
        memset(d_out, 0, sizeof d_out);
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            d[u]++, d[v]++;
            g[u].insert(v);
            g[v].insert(u);
        }
        int t = n;
        for (int i = 0; i < n; i++) {
            if (d[i] % 2 == 1) {
                g[i].insert(t);
                g[t].insert(i);
            }
        }
        go.clear();
        for (int i = 0; i <= n; i++) dfs(i);
        vector <pair <int, int> > res;
        for (auto f : go) {
            if (f.fc != t && f.sc != t) {
                d_out[f.fc]++;
                d_in[f.sc]++;
                res.pb(f);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) ans += (d_in[i] == d_out[i]);
        printf("%d\n", ans);
        for (auto f : res) {
            printf("%d %d\n", f.fc + 1, f.sc + 1);
        }
    }
}

Any positive number n is expressible as a sum of two squares if and only if the prime factorization of n, 
every prime of the form (4k+3) occurs an even number of times.
	public boolean judgeSquareSum(int c) {
        for (int i = 2; i * i <= c; i++) {
            int count = 0;
            if (c % i == 0) {
                while (c % i == 0) {
                    count++;
                    c /= i;
                }
                if (i % 4 == 3 && count % 2 != 0)
                    return false;
            }
        }
        return c % 4 != 3;
    }
