# Table of contents
- [Basics](#basics-)
- [Code for creating array of group size from string](#code-for-creating-array-of-group-size-from-string-)
- [Efficient code for checking prime](#efficient-code-for-checking-prime-)
- [Directions -> `down`, `right`, `up`, `left`](#directions---down-right-up-left-)
- [Longest Increasing Subsequence / LIS](#longest-increasing-subsequence--lis-)
- [Coordinate Compression](#coordinate-compression-)
- [DSU](#dsu-)
- [Sparse Table](#sparse-table-)
- [Finding median of a input stream](#finding-median-of-a-input-stream-)
- [Sweep Line](#sweep-line-)




# Basics [#](#table-of-contents)

```cpp
//prevents floating point errors in ceil((double)a / b) -> a = (ll)1e18 + 1
ll ceil_div(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b != 0); }

ll power(ll a, ll b)
{
    ll res = 1;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
```

# Code for creating array of group size from string [#](#table-of-contents)

```cpp
vector <int> groups;
for (int i = 0; i < n; i++){
    int j = i;
    while (j + 1 < n && s[j + 1] == s[i]){
        j++;
    }

    groups.push_back(j - i + 1);
    i = j;
}
```

# Efficient code for checking prime [#](#table-of-contents)

```cpp
bool isPrime(long long n) {
    if (n == 2 || n == 3) return true;
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) return false;

    //skipping all the multiples of 2 & 3
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
```

# Directions -> `down`, `right`, `up`, `left` [#](#table-of-contents)

```cpp
constexpr int dx[] = {1, 0, -1, 0};
constexpr int dy[] = {0, 1, 0, -1};
/*
d = (d + 1) % 4;
ni = i + dx[d];
nj = j + dy[d]; */
```

# Longest Increasing Subsequence / LIS [#](#table-of-contents)

```cpp
rep(i, n) {
    int a;
    cin >> a;
    // use upperbound for longest non decreasing subseq
    int p = lower_bound(v.begin(), v.end(), a) - v.begin(); //pos of a in vector
    if(p < SZ(v)) v[p] = a;
    else v.pb(a);
}
```

# Coordinate Compression [#](#table-of-contents)

```cpp
vector<int> values;
for (auto &x : nums) values.push_back(x);
sort(values.begin(), values.end());
values.erase(unique(values.begin(), values.end()), values.end());

unordered_map<int,int> idx;
for(int i = 0; i < (int)values.size(); i++) idx[values[i]] = i;

/* this one is shit
int n = a.size();
vector<pair<int, int>> pairs(n);
for(int i = 0; i < n; ++i) pairs[i] = {a[i], i};

sort(pairs.begin(), pairs.end());

int idx = 0;
for(int i = 0; i < n; ++i)
{
	if(i > 0 && pairs[i-1].first != pairs[i].first) idx++;
	a[pairs[i].second] = idx; //changing the values of actual array

    //pairs[modified value].second = original value
    pairs[idx].second = pairs[i].first;
} */
```

# DSU [#](#table-of-contents)

```cpp
int dsu[maxn]; //initialize with -1
int components = n;

// When dsu[x] < 0, x is a root and -dsu[x] is its tree size.
// When dsu[x] >= 0, dsu[x] is x's parent.
int find(int x) { return dsu[x] < 0 ? x : dsu[x] = find(dsu[x]); }

int get_size(int x) { return -dsu[find(x)]; }

bool join(int x, int y)
{
    int p = find(x), q = find(y);
    if(p == q) return 0;

    /* 
    small optimization
    so that less nodes need to update their parent later on
    when you run find queries
    */
    // if sz(p) < sz(q)
    if (-dsu[p] < -dsu[q]) swap(p, q);  

    dsu[p] += dsu[q];  //merging small set into bigger set
    dsu[q] = p; //making p as q's parent

    //components--;
    return 1;
}
```

# Sparse Table [#](#table-of-contents)
```
for n = 8, 1000 -> log2 = 3
for n = 7, 111 -> log2 = 2

          1            8
table[3]  --------------
table[2]  -------
table[1]  --- ---
table[0]  1 2 3 4
```
```cpp
template<typename T>
struct RMQ {
    //log2 of x, use precomputed logs for speedup queries
    static int highest_bit(unsigned x) {        //it's 0th index
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }
 
    int n = 0;
    vector<vector<T>> table;
 
    RMQ(const vector<T> &values = {}) {
        if (!values.empty())
            build(values);
    }
 
    static T better(T a, T b) {
        return a + b;    //customize this
    }
 
    void build(const vector<T> &values) {
        n = int(values.size());
        int levels = highest_bit(n);
        table.resize(levels + 1);
 
        for (int k = 0; k <= levels; k++)
            table[k].resize(n - (1 << k) + 1);
 
        if (n > 0)
            table[0] = values;
 
        for (int k = 1; k <= levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                table[k][i] = better(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
    }
 
    //range is [l, r) O(1)
    T query_value(int l, int r) const {     
        assert(0 <= l && l < r && r <= n);
        int level = highest_bit(r - l);
        return better(table[level][l], table[level][r - (1 << level)]);
    }

    //range is [l, r) O(log_n)
    T query(int l, int r) { 
        // boundaries of next query, 0-indexed 
        T ans = 0;
        int levels = highest_bit(n);
        for (int k = levels; k >= 0; k--) { 
            if (l + (1 << k) <= r) { 
                ans += table[k][l]; 
                l += 1 << k; 
            } 
        } 
        return ans; 
    } 
};
```

# Finding median of a input stream [#](#table-of-contents)

```cpp
multiset<int> lo, hi;
auto push = [&](int x, bool add) {
    if(add) {
        lo.insert(x);

        //necessary for case lo = {1, 2}  hi = {3, 4} & when you are inserting 5
        x = *lo.rbegin();
        lo.erase(prev(lo.end()));
        hi.insert(x);
    }
    else {
        if(*lo.rbegin() >= x) lo.erase(lo.find(x));
        else hi.erase(hi.find(x));
    }

    if(lo.size() < hi.size()) {
        x = *hi.begin();
        lo.insert(x);
        hi.erase(hi.begin());
    }
    else if(hi.size() + 1 < lo.size()) {
        x = *lo.rbegin();
        lo.erase(prev(lo.end()));
        hi.insert(x);
    }

    int median;
    ll tot = lo.size() + hi.size();
    median = *lo.rbegin();

    if(tot % 2 == 0) {
        median += *hi.begin();
        median /= 2.0;
    }

    return median; // only returning the larger median
};
```
---

# Sweep Line [#](#table-of-contents)

```cpp
const int START = 1;
const int END = 2;

struct Event {
    ll x;           // Event position
    int type;       // Event type (START or END)
    int id;         // Interval ID
    
    bool operator<(const Event& other) const {
        // START events before END events at same position
        return tie(x, type) < tie(other.x, other.type);
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<Event> events;
    
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        
        events.push_back({l, START, i});
        events.push_back({r, END, i});
    }
    
    sort(events.begin(), events.end());
    
    set<int> active;

    for (const auto& e : events) {
        if (e.type == START) active.insert(e.id);
        else active.erase(e.id);
        
    }
    
    return 0;
}
```
