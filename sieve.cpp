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
