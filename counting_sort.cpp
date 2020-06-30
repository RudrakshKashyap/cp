for(int j=x;j<=y;j++)
  cnt[s[j] - 'a']++;
ind = 0;
for(int j=x;j<=y;j++)
{
  while(cnt[ind] == 0)
    ind++;
  s[j] = ind + 'a';
  cnt[ind]--;
}


//radix sort
https://codeforces.com/edu/course/2/lesson/2/2
