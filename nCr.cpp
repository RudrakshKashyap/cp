// nCr
// proof at https://cp-algorithms.com/algebra/module-inverse.html

// https://en.wikipedia.org/wiki/Fermat%27s_little_theorem
In number theory, 
Fermat's little theorem states that if p is a prime number,
then for any integer a, the number a^p − a is an integer multiple of p. 

If a is not divisible by p, that is, 
if a is *****COPRIME***** to p, then Fermat's little theorem is equivalent to the statement that a^(p − 1) − 1 is an integer multiple of p,


// TODO https://cp-algorithms.com/algebra/module-inverse.html -->
// check out  Linear Diophantine equation , thingy on this page
const int maxn = 6e5;
ll facinv[maxn + 1];
ll inv[maxn + 1];
ll fac[maxn + 1];

void compute()
{
    fac[0] = 1, fac[1] = 1;
    facinv[0] = 1, facinv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i <= maxn; i++)
    {
        fac[i] = (i * fac[i - 1]) % mod;
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
        facinv[i] = (facinv[i - 1] * inv[i]) % mod;
    }
}

long long nCr(int n, int r) { return ((fac[n] * facinv[r]) % mod * facinv[n - r]) % mod; }
// lucas theom proof https://cp-algorithms.com/algebra/factorial-modulo.html
// https://www.youtube.com/watch?v=vWV3yeBD-Gw
// https://en.wikipedia.org/wiki/Lucas%27s_theorem
