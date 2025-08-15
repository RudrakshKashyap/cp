
- classic complexity is o(n log(log(n))), 
- for o(n) complexity check out https://www.geeksforgeeks.org/sieve-eratosthenes-0n-time-complexity/
- https://www.geeksforgeeks.org/how-is-the-time-complexity-of-sieve-of-eratosthenes-is-nloglogn/


```cpp
const int maxn = 1e6;
int se[maxn + 1];
vector<int> primes;

void sieve()
{
    se[0] = 1, se[1] = 1;
    primes = {};

    for(int i = 2; i <= maxn; i++)
    {
        if(!se[i])
        {
            primes.emplace_back(i);

            for(int j = i; j <= maxn; j += i)
            {
                if(!se[j])
                    se[j] = i;
            }
        }
    }
}

// Prime factorizes n in worst case
// for each query O(sqrt n / log n). 
// Requires having run `sieve` up to at least maxn = sqrt(n).
vector<pair<ll, int>> prime_factorize(ll n)
{
    assert(1 <= n && n <= (ll)maxn * maxn);

    vector<pair<ll,int>> result;

    //worst case -> O(log_n) if n is power of 2
    if (n <= maxn)
    {
        while (n != 1)
        {
            ll p = se[n];
            int exponent = 0;

            do {
                n /= p;
                exponent++;
            } while (n % p == 0);

            result.emplace_back(p, exponent);
        }

        return result;
    }

    //eg -> n = 2 * 104,729
    //O(sqrt_n)[when n = sqrt_n*sqrt_n] or O(log_n)[n = 2^p]
    for (ll p : primes)
    {
        if (p * p > n) break;

        if (n % p == 0)
        {
            int exponent = 0;

            do {
                n /= p;
                exponent++;
            } while (n % p == 0);
            
            result.emplace_back(p, exponent);
        }
    }

    //n = 104,729 after above loop ends
    if (n > 1)
        result.emplace_back(n, 1);

    return result;
}
```