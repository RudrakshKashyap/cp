/**         (buri nazar wale tera muh kala 😑)
 *
 * @Author   : rudraksh
 * @Created  : Friday, May 29th 2020, 1:54:11 pm
 * @Email    : rudrakshk@iitbhilai.ac.in
 *
 *  WARNING  : Don't look at my code, i write shit.
 *             You won't be able to understand anything and may end up wasting time.
 *
 */


#include<bits/stdc++.h>
// #include<unistd.h>
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
#define loop(it,x) for(auto it=x.begin();it!=x.end();it++)
#define all(x) (x).begin(),(x).end()
#define MS0(x) memset((x), 0, sizeof((x)))
#define MS1(x) memset((x), -1, sizeof((x)))
#define CP(dst,src) memcpy(dst, src, sizeof(src));
#define SZ(x) ((ll)(x).size())
#define watch(x) cout << (#x) << " is " << (x) << "\n"
#define TIME    cerr << "\nTime elapsed: " << setprecision(5) <<1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";

const ll mod=1e9+7;
const double pi=acos(-1);

ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
// ll power(ll a,ll b,ll p) //log(y)
// {
//     ll res=1;
//     a%=p;
//     if(a==0) return 0;
//     while(b>0)
//     {
//         if(b&1) res=(res*a)%p;
//         b=b>>1;
//         a=(a*a)%p;
//     }
//     return res;
// }
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


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;
    while(t--)
    {

    }
    return 0;
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
