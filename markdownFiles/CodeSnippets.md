
* Code for creating array of group size from string
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

* Efficient code for checking prime
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

* Directions -> `down`, `right`, `up`, `left`
    ```cpp
    constexpr int dx[] = {1, 0, -1, 0};
    constexpr int dy[] = {0, 1, 0, -1};
    /*
    d = (d + 1) % 4;
    ni = i + dx[d];
    nj = j + dy[d]; */
    ```

* Longest Increasing Subsequence / LIS
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


* Finding medain of a input stream
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
        if(tot % 2 == 0) median = *hi.begin();
        else median = *lo.rbegin();
        
        return median; // only returning the larger median
    };
    ```
