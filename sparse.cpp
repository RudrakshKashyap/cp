const int k = 16;   //maxlog floor
const int maxn = 1e5;  //maxn

int n;  //size of arr
long long table[maxn][k + 1]; // k + 1 because we need to access table[r][MAXLOG]
int arr[maxn];
int numlog[maxn+1];


void build()
{
    numlog[1] = 0;
    for (int i = 2; i <= n; i++)
        numlog[i] = numlog[i / 2] + 1;      //will give floor of log

    // build Sparse Table
    for(int i = 0; i < n; i++)
        table[i][0] = arr[i];
    for(int j = 1; j <= numlog[n]; j++)
    {
        for(int i = 0; i <= n - (1 << j); i++)
            table[i][j] = table[i][j - 1] + table[i + (1 << (j - 1))][j - 1];
    }
}

int getMax(int l, int r)    //these l and r are inclusive [l,r]
{
    int curlog = numlog[r - l + 1];
    return max(table[l][curlog], table[r - (1 << curlog) + 1][curlog]);
}

long long query(int l, int r) 
{ 
    // boundaries of next query, 0-indexed 
    long long answer = 0; 
    for (int j = numlog[n]; j >= 0; j--) { 
        if (l + (1 << j) - 1 <= r) { 
            answer = answer + table[l][j]; 
  
            // instead of having L', we 
            // increment L directly 
            l += 1 << j; 
        } 
    } 
    return answer; 
} 




//////////////////////

template<typename T, bool maximum_mode = false>
struct RMQ {
    static int highest_bit(unsigned x) {        //it's 0th index
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }
 
    int n = 0;
    vector<vector<T>> range_min;
 
    RMQ(const vector<T> &values = {}) {
        if (!values.empty())
            build(values);
    }
 
    static T better(T a, T b) {
        return maximum_mode ? max(a, b) : min(a, b);
    }
 
    void build(const vector<T> &values) {
        n = int(values.size());
        int levels = highest_bit(n) + 1;
        range_min.resize(levels);
 
        for (int k = 0; k < levels; k++)
            range_min[k].resize(n - (1 << k) + 1);
 
        if (n > 0)
            range_min[0] = values;
 
        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_min[k][i] = better(range_min[k - 1][i], range_min[k - 1][i + (1 << (k - 1))]);
    }
 
    T query_value(int a, int b) const {     //range is [l, r)
        assert(0 <= a && a < b && b <= n);
        int level = highest_bit(b - a);
        return better(range_min[level][a], range_min[level][b - (1 << level)]);
    }
};

