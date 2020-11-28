rep(i,n)
{
    rep(oldmask, 1<<n)
    {
        int mask = oldmask ^ ( (1<<n) - 1);
        for(int newmask = mask; newmask >= 0; newmask = (newmask - 1)&mask)
        {
            // new mask will take elements which you left in old mask
            dp[i+1][oldmask | newmask] = max(dp[i+1][oldmask | newmask], dp[i][oldmask] + sum);
            if(newmask == 0) break;
        }
    }
