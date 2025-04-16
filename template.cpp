https://www.youtube.com/watch?v=o1EvPhz6UNE
https://www.youtube.com/watch?v=9D8uPKDffdI
https://www.geeksforgeeks.org/variadic-function-templates-c/


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

bool isPrime(long long n) {
    if (n == 2 || n == 3) return true;
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) return false;

    //skipping all the multiples of 2 & 3
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
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
