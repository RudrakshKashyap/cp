https://atcoder.jp/contests/dp/tasks/dp_n --> optimize with knuth's optimization

- [SOS Dynamic Programming [Tutorial]](https://codeforces.com/blog/entry/45223)
```cpp
/*
https://codeforces.com/blog/entry/45223
at iteration 'i'
	dp[mask] => bits(N....i+1) of mask = fixed / all subset of mask from bits(i.....0)
*/

int N = static_cast<int>(floor(log2(max_val))) + 1;
for(int i = 0; i < (1 << N); i++)
	dp[i] = A[i];

for(int i = 0; i < N; i++) {
	for(int mask = 0; mask < (1 << N); mask++)
		if(mask & (1 << i))
			dp[mask] += dp[mask ^ (1 << i)];
}

```




- [Some SOS DP Insights](https://codeforces.com/blog/entry/105247)
  
```
3^N complexity

AT -> already taken
T -> taken now
E -> empty/not taken

AT AT AT T T E T AT E AT T T E AT E E -> 3 possible choices
```

If a mask has K on bits, we do 2K iterations.
Also total number of masks with K on bits is ![](https://espresso.codeforces.com/7a5098129ec396690eff661a2912af20608e5dd2.png).
Therefore total iterations = ![](https://espresso.codeforces.com/d6edea98b37d05f4f4da97404cf233680560eedd.png)


```cpp
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
```
