/**         (buri nazar wale tera muh kala 😑)
 *
 * @Author   : rudraksh
 * @Created  : Tuesday, May 26th 2020, 1:33:02 pm
 * @Email    : rudrakshk@iitbhilai.ac.in
 *
 *   Always give 100% — unless you’re donating blood.
 */


 //https://codeforces.com/blog/entry/18051
 //bottom up approach


#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;  // limit for array size
int n;  // array size
int t[2 * N];

void build()
{
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value)
{
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) // sum on interval [l, r) remember we are excluding r
{
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
}

int main() {
  cin>>n;
  for(int i=0;i<n;i++) cin>>t[i+n];
  build();
  modify(0, 1);
  printf("%d\n", query(3, 11));
  return 0;
}




Some people begin to struggle and invent something too complex when the operations are inverted, for example:

1) add a value to all elements in some interval;
2) compute an element at some position.
But all we need to do in this case is to switch the code in methods modify and query as follows:

void modify(int l, int r, int value) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}

int query(int p) {
  int res = 0;
  for (p += n; p > 0; p >>= 1) res += t[p];
  return res;
}
