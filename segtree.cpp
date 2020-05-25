/**         (buri nazar wale tera muh kala 😑)
 *
 * @Author   : rudraksh
 * @Created  : Monday, May 25th 2020, 3:50:53 pm
 * @Email    : rudrakshk@iitbhilai.ac.in
 *
 *  WARNING  : Don't look at my code, i write shit.
 *             You won't be able to understand anything and may end up wasting time.
 *
 */

 //https://www.hackerearth.com/zh/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
 //https://www.youtube.com/watch?v=BuoG-1KC4qs

#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int,int> PI;
typedef pair<ll,ll> PL;
typedef map<int,int> MI;
typedef vector<VI> VVI;
typedef pair<int,PI> PIP;

#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define mp make_pair
#define repa(i,a,n) for(ll i=a;i<n;i++)
#define rep(i,n) for(ll i=0;i<n;i++)
#define pera(i,a,n) for(ll i=a;i>=n;i--)
#define per(i,n) for(ll i=n;i>=0;i--)
#define all(x) (x).begin(),(x).end()
#define loop(it,x) for(auto it=x.begin();it!=x.end();it++)
#define MS0(x) memset((x), 0, sizeof((x)))
#define MS1(x) memset((x), -1, sizeof((x)))
#define CP(dst,src) memcpy(dst, src, sizeof(src));
#define SZ(x) ((ll)(x).size())
#define TIME    cerr << "\nTime elapsed: " << setprecision(5) <<1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";

const ll mod=1e9+7;
const double pi=acos(-1);

ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll power(ll a,ll b,ll p) //log(b)
{
    if(b==0) return 1;
    ll c = power(a,b/2,p);
    if(b%2==0) return (c*c)%p;
    else return (((c*c)%p)*a)%p;
}
ll inv(ll n, ll p){ return power(n,p-2, p); }
bool isPrime(ll n) {
    if (n <= 1)  return false;
    if (n <= 3)  return true;
    if (n%2 == 0 || n%3 == 0) return false;
    for (ll i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;
    return true;
}

int tree[40005];

void build(int node, int start, int end, int A[])   //build(1,0,n-1,a);
{
    if(start == end) tree[node] = A[start];
    else
    {
        int mid = (start + end) / 2;
        build(2*node, start, mid, A);
        build(2*node+1, mid+1, end, A);

        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void update(int node, int start, int end, int idx, int val, int A[])
{
    if(start == end)
    {
        // Leaf node
        A[idx] += val;
        tree[node] += val;
    }
    else
    {
        int mid = (start + end) / 2;
        if(start <= idx and idx <= mid)
            update(2*node, start, mid, idx, val, A);
        else
            update(2*node+1, mid+1, end, idx, val, A);
        // Internal node will have the sum of both of its children
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

int query(int node, int start, int end, int l, int r)
{
    if(r < start or end < l)
    {
        // range represented by a node is completely outside the given range
        return 0;
    }
    if(l <= start and end <= r)
    {
        // range represented by a node is completely inside the given range
        return tree[node];
    }
    // range represented by a node is partially inside and partially outside the given range
    int mid = (start + end) / 2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node+1, mid+1, end, l, r);
    return (p1 + p2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);



    return 0;
}
