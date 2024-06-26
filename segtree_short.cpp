/**         (buri nazar wale tera muh kala 😑)
 *
 * @Author   : rudraksh
 * @Created  : Wednesday, May 27th 2020, 10:46:34 am
 * @Email    : rudrakshk@iitbhilai.ac.in
 *
 *   Always give 100% — unless you’re donating blood.
 */


 //https://codeforces.com/blog/entry/18051


#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;  // limit for array size
int n;  // array size
int t[2 * N];

void build()    //building bottom to up
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












//https://codeforces.com/blog/entry/18051?#comment-342885
This entry explains for Assigment in range, sum in range — and it is difficult than increment operation.
But, If you want increment in range, it simple than assignment.
Let Theory, again; 1<=n<=N ~ 10^5. a[0], a[1], ... , a[n-1] — given array. Need apply two operations:
increment a[L], a[L+1],... a[R-1] to value, i.e [L..R) range.
find sum a[L] + a[L+1] + ... + a[R-1] , i.e. [L..R) range.
t[0..n+n] — segment tree array. d[0..n+n] — lazy propogation.
where
t[i] = a[ i — n], n<=i < n+n. and
t[i] = t[i*2] + t[i*2+1], for 0<=i<n.
If a[i] incremented by value, so t[i+n] also incremented by value.
if t[i*2] and t[i*2+1] incremented by value, they root t[i] incremented 2* value. and its applied recursive down.

In general, if all leaf nodes of i-th root incremented by value, so t[i] should increment the value multiply number of leaf children of i-th root.
for example: n = 8. if a[4] , a[5], a[6], a[7] increment by 5, so t[12], t[13], t[14], t[15] incremented by 1*5, t[6], and t[7] — incremented by 2*5, and t[3] incremented by 4*5. t[3] — has 4 children.

Now, about lazy propogation d[] array. d[ i ] == 0, means there no increment operation i-th root. d[i] > 0, means all leaf nodes from i-th root of segment tree will increment by d[i], and applied 2.step operation recursivily.
If we need increment [L..R)  range by `value` , need increment only root nodes by  `value` * children(i), and d[i] increments by `value`.  Other nodes will calculated some later.
For example: if need increment a[4..7] to 5. There only increment t[3] to 5*4, and put d[3] = 5. This apply operation. Other nodes t[6], t[7], t[12], t[13], t[14], t[15] nodes will incremented some later (may never).

#define N 100008

int t[N+N];
int d[N+N]; //actually we can just take d[N];
//int ch[N+N]; // number of children .
int n;

void apply (int p, int value, int children)
{
    t[ p ] += value * children;
    if (p < n ) d[p] += value.
}

void build(int p) // fixes applied nodes and down nodes.
{
    int children = 1;
     while (p > 1)
     {
           p = p  /  2 ;
           children = children * 2;
           t[p] = t[ p * 2] + t[ p * 2 + 1] + d[ p ] * children;
     }
}

void push(int p) // calculate lazy operations from p nodes.
{  // h = log2(n).
     for(int s = h ; s > 0 ; --s)
     {
            int i = p >> s; // i = p / 2^s
            if ( d[i] != 0 )
            {
 // so i*2 and i*2+1 nodes will increase by
//  d[i] * children,  where children = 2^(s-1)
                   int children = 1 << (s-1);
                   apply(i*2, d[i], children);
                   apply(i*2+1, d[i], children);

              // now d[i] - is dont need no more, clear it.
                  d[i] = 0;
            }
     }
}


int increment(int L, int R, int value)
{
     L += n, R += n;
     int L0 = L, R0 = R; //presave they.
for( int children = 1 ; L < R ;  L/=2, R/=2, children *= 2)
     {
           if (L % 2 == 1) // L - root node
              apply(L++, value, children);

           if ( R % 2 == 1) // R - 1  root node
              apply(--R, value, children);
      }

    // now fix applied nodes and downsite nodes.
     build(L0);
     build(R0-1);
}


int sumRange(int L, int R)
{
      // need calculate applied nodes from L and R.
      L += n, R+= n;
      push(L); push(R-1); // it clears all lazy d[] nodes.
      int sum = 0;
      for( ; L < R; L /= 2, R/=2)
      {
            if (L % 2 == 1) sum += t[L++];
            if (R % 2 == 1) sum += t[ --R];
      }
     return sum;
}



















//image http://i.imgur.com/GGBmcEP.png
#include <iostream>
#include <cstdlib>
using namespace std;
const int n = 1<<18;
int t[2*n];
int h = sizeof(int) * 8 - __builtin_clz(n);
int d[n];
void apply(int p, int value) {
    t[p] += value;
    if (p < n) d[p] += value;
}

void build(int p) {     //we go from bottom to up  //we fix elements
    while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
}

void push(int p) {  //we go from top to down
    for (int s = h; s > 0; --s) {
        int i = p >> s;
        if (d[i] != 0) {
            apply(i<<1, d[i]);
            apply(i<<1|1, d[i]);
            d[i] = 0;
        }
    }
}

void inc(int l, int r, int value) {
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, value);     //we apply value to only corner elements
        if (r&1) apply(--r, value);
    }
    build(l0);      //if l0=19 then we fix node 9 --- check in image
    build(r0 - 1);
}

int query(int l, int r) {
    l += n, r += n;
    push(l);    //applying pending d[] values
    push(r - 1);
    int res = -2e9;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = max(res, t[l++]);
        if (r&1) res = max(t[--r], res);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    for(int i = 0; i < 1e7; ++i) {
        if(rand()&1) {
            int q = rand()%n;
            int w = rand()%n;
            if(q > w) swap(q, w);
            int e = rand()%100;
            inc(q, w+1, e);
        }
        else {
            int q = rand()%n;
            int w = rand()%n;
            if(q > w) swap(q, w);
            int ans = query(q, w+1);;
            cout<<ans<<'\n';
        }
    }
}
