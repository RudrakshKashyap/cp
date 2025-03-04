int l = 0, r = 0, sum = 0;
while(r <= n)
{
    if(sum < k)
    {
        if(r < n) sum += a[r];
        r++;
    }
    if(sum > k)
    {
        sum -= a[l];
        l++;
    }
    if(sum == k)
    {
        amin(ans, r - l);
        sum -= a[l];
        l++;
    }
}




//////////////////////////////
int l = 0;
rep(i, n)
{
    sum += a[i];
    while(sum >= k)
    {
        if(sum == k) ans = i - l + 1;
        sum -= a[l++];
    }
}
////////////////////////////////////////////////
int l = 0, r = 0, sum = 0, min = Integer.MAX_VALUE;
  
  while (r < n) {
    sum += a[r++];
    
    while (sum >= s) {
      min = Math.min(min, r - l);
      sum -= a[l++];
    }
  }
