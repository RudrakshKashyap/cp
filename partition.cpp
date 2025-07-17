//https://atcoder.jp/contests/dp/tasks/dp_n --> optimize with knuth's optimization

3^N complexity

AT -> already taken
T -> taken now
E -> empty/not taken

AT AT AT T T E T AT E AT T T E AT E E -> 3 possible choises

rep(oldmask, 1 << n)
{
    int mask = oldmask ^ ((1 << n) - 1);
    for(int newmask = mask; newmask >= 0; newmask = (newmask - 1) & mask)
    {
        // new mask will take elements which you left in old mask
        dp[i+1][oldmask | newmask] = max(dp[i+1][oldmask | newmask], dp[i][oldmask] + sum);
        if(newmask == 0) break;
    }
}
