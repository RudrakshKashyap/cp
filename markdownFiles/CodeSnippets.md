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

* directions -> down, right, up, left
    ```cpp
    constexpr int dx[] = {1, 0, -1, 0};
    constexpr int dy[] = {0, 1, 0, -1};
    /*
    d = (d + 1) % 4;
    ni = i + dx[d];
    nj = j + dy[d]; */
    ```
