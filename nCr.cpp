// nCr
//proof at https://cp-algorithms.com/algebra/module-inverse.html
const int maxn = 6e5;
ll facinv[maxn];
ll inv[maxn];
ll fac[maxn];

void compute()
{
    fac[0] = 1, fac[1] = 1;
    facinv[0] = 1, facinv[1] = 1;
    inv[1] = 1;
    for(int i=2 ; i < maxn ; i++)
    {
    	fac[i] = (i * fac[i-1]) % mod;
    	inv[i] = ((mod - mod/i) * inv[mod%i]) % mod;
    	facinv[i] = (facinv[i-1] * inv[i]) % mod;
    }
}

long long nCr(int n, int r) { return ((fac[n] * facinv[r])%mod * facinv[n-r]) % mod;}
//lucas theom proof https://cp-algorithms.com/algebra/factorial-modulo.html
