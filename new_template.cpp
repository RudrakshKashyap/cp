/**         (buri nazar wale tera muh kala 😑)
 *
 * @Author   : rudraksh
 * @Created  : Wednesday, January 13th 2021, 11:48:10 pm
 * @Email    : rudrakshk@iitbhilai.ac.in
 *
 *   “My code works? - don't ask me how”
 */


#include <bits/stdc++.h>
#include <unistd.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;

typedef long long int ll;
typedef double db;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int,int> PI;
typedef pair<ll,ll> PL;
typedef map<int,int> MI;
typedef map<ll,ll> ML;

#define ar              array
#define pb              push_back
#define pf              push_front
#define popb            pop_back
#define popf            pop_front
#define eb              emplace_back
#define F               first
#define S               second
#define repa(i,a,n)     for(ll i=a;i<n;i++)
#define rep(i,n)        for(ll i=0;i<n;i++)
#define pera(i,a,n)     for(ll i=a;i>=n;i--)
#define per(i,n)        for(ll i=n;i>=0;i--)
#define all(x)          (x).begin(),(x).end()
#define loop(it,x)      for(auto it=x.begin();it!=x.end();it++)
#define MS0(x)          memset((x), 0, sizeof((x)))
#define MS1(x)          memset((x), -1, sizeof((x)))
#define CP(dst,src)     memcpy(dst, src, sizeof(src))
#define SZ(x)           ((ll)(x).size())
#define watch(x)        cout << (#x) << " is " << (x) << endl
#define TIME            cerr << "\nTime elapsed: " << setprecision(5) << 1000.0*clock()/CLOCKS_PER_SEC << "ms\n";

const ll mod = 1e9+7;
const double pi = acos(-1);

template<typename T> using minpq = priority_queue<T, vector<T>, greater<T>>;

// oset.insert({x, id++}); for multiset. Better than less_equal<T>,erase won't work & lb work as ub and vice versa
template<typename T, typename Comp = less<T> >
using oset = tree<T, null_type, Comp, rb_tree_tag, tree_order_statistics_node_update>;

//find_by_order(k)  --> value at kth index (iterator)
//order_of_key(k)   --> no of elements strictly less than k (0 based index)
template<typename T, typename T1, typename Comp = less<T> >
using omap = tree<T, T1, Comp, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>ostream& operator<<(ostream& out,vector<T>& v){for(auto& x: v)out<<x<<' '; return out;}
template<typename T>istream& operator>>(istream& in,vector<T>& v){for(auto& x: v)cin>>x; return in;}

template<typename T,typename T1>bool amax(T &a,T1 b){if(b>a){a=b; return 1;} return 0;}
template<typename T,typename T1>bool amin(T &a,T1 b){if(b<a){a=b; return 1;} return 0;}

void print() { cout<<'\n'; }
// void print() { cout<<endl; }

template <typename T, typename... Params>
void print(T var1, Params... var2) {cout<<var1<<' '; print(var2...);}


ll ceil_div(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b != 0); }

ll power(ll a, ll b)
{
    ll res = 1;
    a %= mod;
    while(b > 0)
    {
        if(b&1) res = (res*a) % mod;
        b >>= 1;
        a = (a*a) % mod;
    }
    return res;
}


/************* I don't know what i'm doing ****************/



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);



    return 0;
}
