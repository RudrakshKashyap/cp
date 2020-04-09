#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

typedef long long int ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int,int> PI;
typedef pair<ll,ll> PL;
// typedef map<int,int> mi;

//#define endl '\n'
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
#define MS0(x) memset((x), 0, sizeof((x)))
#define MS1(x) memset((x), -1, sizeof((x)))
#define MEM(a, b) memset(a, b, sizeof(a))
#define SZ(x) ((ll)(x).size())
#define TIME    cerr << "\nTime elapsed: " << setprecision(5) <<1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";

const ll mod=1e9+7;
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll power(ll a,ll b,ll p)
{
    if(b==0) return 1;
    ll c = power(a,b/2,p);
    if(b%2==0) return (c*c)%p;
    else return (((c*c)%p)*a)%p;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll t;
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
