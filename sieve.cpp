//classic complexity is o(n log(log(n))), for o(n) complexity check out https://www.geeksforgeeks.org/sieve-eratosthenes-0n-time-complexity/
//https://www.geeksforgeeks.org/how-is-the-time-complexity-of-sieve-of-eratosthenes-is-nloglogn/

int ar[10001];
int maxn = 10001;

void sieve()
{
    repa(i,1,maxn+1) ar[i]= -1;

    repa(i,2,maxn+1)
        if(ar[i]==-1)
            for(int j=i;j<=maxn; j+=i)
                if(ar[j]==-1)
                    ar[j]=i;
}

/////////////////////////////
const int maxn = 1e6;
int se[maxn+1];
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
// for each query O(sqrt n / log n). Requires having run `sieve` up to at least sqrt(n).
vector<pair<ll, int>> prime_factorize(ll n)
{
    assert(1 <= n && n <= (ll)maxn * maxn);

    vector<pair<ll,int>> result;

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

    if (n > 1)
        result.emplace_back(n, 1);

    return result;
}
