http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3424.pdf

vector<bool> mark(Alp);
function<void(int)> dfs = [&](int u)    // [&] means capturing by reference
{
    mark[u] = true;
    for (auto v : adj[u])
        if (!mark[v])
            dfs(v);
};

Note that mark is a vector, because if we want to use array like int mark[len] then len should be given before compiling. we cant use variable size

A lambda with empty capture clause [ ] can access only those variable which are local to it, i.e. you cant access mark[u] array in dfs or other variable which are declared in main
[=] means capturing by value
[a, &b] : capture a by value and b by reference
// a is read-only (captured by value)
// b can be modified (captured by reference)


correct
auto dfs = [&](int u)
{
    print(__PRETTY_FUNCTION__);
    return u;
};

correct
                       // return type
auto dfs = [&](int u) -> int
{
    print(__PRETTY_FUNCTION__);
    return u;
};


wrong
auto dfs = [&](int u)
{
    mark[u] = true;
    for (auto v : adj[u])
        if (!mark[v])
            dfs(v);     //use of dfs before deduction of auto error
};








//https://www.youtube.com/watch?v=9T8A89jgeTI&ab_channel=Computerphile
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
 
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
 
template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

y_combinator([&](auto recurse, int start, int end) -> void {
        if (start >= end)
            return;
 
        if (!done.emplace(start, end).second)
            return;
 
        sums.insert(prefix_sum[end] - prefix_sum[start]);
        int minimum = A[start];
        int maximum = A[end - 1];
        int cutoff = (minimum + maximum) / 2;
        int split = int(upper_bound(A.begin(), A.end(), cutoff) - A.begin());
        recurse(start, split);
        recurse(split, end);
    })(0, N);
