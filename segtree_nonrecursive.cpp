/**         (buri nazar wale tera muh kala 😑)
 *
 * @Author   : rudraksh
 * @Created  : Wednesday, May 27th 2020, 10:46:34 am
 * @Email    : rudrakshk@iitbhilai.ac.in
 *
 *   Always give 100% — unless you’re donating blood.
 */


 //https://codeforces.com/blog/entry/18051

A strictly binary tree, also known as a full binary tree or proper binary tree, is a type of binary tree in which every node has either exactly two children or none (i.e., each node is either an internal node with two children or a leaf node with no children). 
Assume that for a strictly binary tree with k leaves, the total number of nodes is 
2k−1. Now, consider a strictly binary tree with k+1 leaves.

In a strictly binary tree, every internal node has exactly two children. To increase the number of leaves from k to 
k+1, we can select an existing leaf node and add two child nodes to it. 
This transforms the selected leaf into an internal node with two children, effectively adding two new nodes to the tree.
By the principle of mathematical induction, the statement is true for all 
n≥1: a strictly binary tree with 
n leaves always contains 2n−1 nodes.


it takes t[2n] memory bc t[0] is useless

///////////////////////////

below we are just creating a binary tree with n leaves, -> number of extra nodes = n 

                                                      1: [0, 16) r

                                2: [0, 8) l                                                  3: [8, 16) r

            4: [0, 4) l                     5: [4, 8) r                          6: [8, 12) l                        7: [12, 16) r

  8: [0, 2) l        9: [2, 4) r       10: [4, 6)      11: [6, 8)          12: [8, 10)      13: [10, 12)        14: [12, 14)       15: [14, 16)

16: 0   17: 1   18: 2   19: 3   20: 4 l   21: 5 r      22: 6   23: 7     24: 8   25: 9      26: 10  27: 11     28: 12   29: 13     30: 14   31: 15

we consider range [L, R+1)

 we go in left to Right direction from node L, and right to left direction from node R+1

 i.e.  L -------->...        mid      ...<------------R+1
      type 1                               type2
 during this process, when going from L to mid
if we are at node type 'r'(right node), that means it is fully in range, take it and increase L++, then L/=2

similarly when going from R + 1 to mid, 
 if we are at node type 'r'(right node), that means the left node is fully in range, so we take left node, then R/=2 which is basically the same as R-1/2

*****************

 or i think we can do is go from mid ...<-------------R
 in this case code should be if(R&1 == 0) res+=t[r--], and loop till l<=r, this code should still work
yes it will work i just read in comments, but other functions should be changed accordingly as well
 
 ***********

 
 General idea is the following. 
 If l, the left interval border, is odd (which is equivalent to l&1) then l is the right child of its parent. 
 Then our interval includes node l but doesn't include it's parent. 
 So we add t[l] and move to the right of l's parent by setting l = (l + 1) / 2. 
If l is even, it is the left child, and the interval includes its parent as well (unless the right border interferes), 
so we just move to it by setting l = l / 2. Similar argumentation is applied to the right border. 
We stop once borders meet.



 //////////////////////////
 
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




Some people begin to struggle and invent something too complex when the operations are inverted, for example

1) add a value to all elements in some interval; ofcourse everything is 0 initially dumbass
2) compute an element at some position.
But all we need to do in this case is to switch the code in methods modify and query as follows

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


Non-commutative combiner functions
For now we considered only the simplest combiner function — addition. 
It is commutative, which means the order of operands doesn't matter, 
 we have a + b = b + a. 
 The same applies to min and max, so we can just change all occurrences of + to one of those functions and be fine. 
 But don't forget to initialize query result to infinity instead of 0.

However, there are cases when the combiner isnt commutative,
 for example, in the problem 380C - Sereja and Brackets, tutorial available here http://codeforces.com/blog/entry/10363.
Fortunately, our implementation can easily support that.
 We define structure S and combine function for it. In method build we just change + to this function. 
 In modify we need to ensure the correct ordering of children, knowing that left child has even index. 
 When answering the query, we note that nodes corresponding to the left border are processed from left to right, 
while the right border moves from right to left. We can express it in the code in the following way



void modify(int p, const S& value) {
  for (t[p += n] = value; p >>= 1; ) t[p] = combine(t[p<<1], t[p<<1|1]);
}

S query(int l, int r) {
  S resl, resr;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) resl = combine(resl, t[l++]);
    if (r&1) resr = combine(t[--r], resr);
  }
  return combine(resl, resr);
}


Lazy propagation-->------------------------------------------------------------>
 Increment modifications, queries for maximum
d[i] is a delayed operation to be propagated to the children of node i, 
 means if d[p]!=0, it is already included in t[p] but not in it's children


 int h = sizeof(int) * 8 - __builtin_clz(n);
int d[N];  
void apply(int p, int value) {
  t[p] += value;
  if (p < n) d[p] += value;
}

void build(int p) {
  while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
}

void push(int p) {
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
    if (l&1) apply(l++, value);
    if (r&1) apply(--r, value);
  }
  build(l0);
  build(r0 - 1);
}

int query(int l, int r) {
  l += n, r += n;
  push(l);
  push(r - 1);
  int res = -2e9;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(t[--r], res);
  }
  return res;
}
build is designed to update all the parents of a given node.
 node 19 affects nodes 9, 4, 2 and 1, node 5 affects 2 and 1. so to fix we need build after each range increment


NOTE NOTE NOTE NOTE NOTE NOTE
Modification on interval [l, r) affects t[i] values only in the parents of border leaves: l+n and r+n-1 
 (except the values that compose the interval itself — the ones accessed in for loop).

 the above sentence mean, the nodes that makes sum of range [l,r] => 
can only come from nodes that lies in the 
 path from root to l, and path from root to r or their immediate children,
 you can just confirm it from the picture, path from root to 19 & root to 26 includes 
nodes [1,2,4,9,19 + 1,3,6,13,26] 
 range[19,26] consist of node 9,5,12,26 which comes from above set of nodes or their immediate children,eg. 5 is children of 2
 so only fixing push(19),push(26) will do our job for query l,r




 so if we push(l), push(r) that means we are ready for query [l,r]
push(x) function just fixes the children of node x
push(l) -> we are fixing all the nodes(this includes both child getting fixed) from child of root to leaf 'l'


It's easy to see that all operations above take O(log(n)) time.

Again, this is the simplest case because of two reasons:

order of modifications doesn't affect the result;
when updating a node, we don't need to know the length of interval it represents.

 Assignment modifications, sum queries-> just read this from the blog

Main methods don't change much from the last example, but modify has 2 things to notice:

Because the order of modifications is important, we need to make sure there are no old changes on the paths from the root to all the nodes we're going to update. This is done by calling push first as we did in query.
We need to maintain the value of k.

 Both this methods work on any interval in O(log(n) + |r - l|) time. -> O(|r-l|) because think of
a binary tree with last row of size r-l, number of nodes will be like 2*(r-l) +-1 something something
If we want to transform some interval in the tree, we can write code like this:
 
 push(l, r);
...  // do anything we want with elements in interval [l, r) -> this includes changing a[l] to 'a' a[l+1] to 'b' ... basically changing every value
build(l, r);

if u want to just change interval with same value just push(l & r) build(l & r) -> logn complexity


One could notice that we do 3 passed in modify over almost the same nodes: 
1 down the tree in push, then 2 up the tree. We can eliminate the last pass and calculate new values only 
where it's necessary, but the code gets more complicated
--> i dont have the time nor energy to read this last section
 
-----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------
from comments


 
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
