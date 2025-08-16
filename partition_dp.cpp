//https://atcoder.jp/contests/dp/tasks/dp_n --> optimize with knuth's optimization

3^N complexity

AT -> already taken
T -> taken now
E -> empty/not taken

AT AT AT T T E T AT E AT T T E AT E E -> 3 possible choises


rep(oldmask, 1 << n)
{
    int mask = oldmask ^ ((1 << n) - 1);
    for(int submask = mask; submask > 0; submask = (submask - 1) & mask)
    {
        /* submask will take elements which you left in old mask
            submask will be generated in decreasing order
            eg -> mask =        110101011
            cur submask =       110100000
            next submask =      110001011
            bc whenever you are removing curLast bit,
            you are also setting previous bits to 1
        */
        dp[i+1][oldmask | submask] = max(dp[i+1][oldmask | submask], dp[i][oldmask] + dp[i][submask]);
        /* uncomment & change loop condition to >= 0
            if you need submask = 0 for some reason,
            since oldmask already start from 0 so no need
        */
        // if(submask == 0) break; 
    }
}
