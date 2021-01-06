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

void sieve()
{
    se[0] = 1, se[1] = 1;
    for(int i = 2; i <= maxn; i++)
    {
        if(!se[i])
        {
            for(int j = i; j <= maxn; j += i)
            {
                if(!se[j])
                    se[j] = i;
            }
        }
    }
}
