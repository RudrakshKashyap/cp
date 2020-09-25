// nCr
//proof at https://cp-algorithms.com/algebra/module-inverse.html
ll facinv[600000];
ll inv[600000];
ll fac[600000];
fac[0]=1; facinv[0]=1;
inv[1]=1; fac[1]=1; facinv[1]=1;
for(i=2 ; i<=599999 ; i++)
{
	fac[i]=(i*fac[i-1])%mod;
	inv[i]=((mod-mod/i)*inv[mod%i])%mod;
	facinv[i]=(facinv[i-1]*inv[i])%mod;
}
//lucas theom proof https://cp-algorithms.com/algebra/factorial-modulo.html
