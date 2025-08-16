
### For the array `[1, 2, 3, 4, 5, 6]`:
```
                              (1)
                      [1,2,3,4,5,6]                     level 0
                     /               \
                (2)                   (3)
           [1,2,3]                 [4,5,6]              level 1
           /     \                 /     \
        (4)     (5)             (6)     (7)
      [1,2]     [3]           [4,5]     [6]             level 2
      /   \                   /   \
    (8)   (9)               (12)  (13)
   [1]    [2]              [4]    [5]                   level 3

   You can see at level 2, our tree has created 4 leaves but
   it was not enough to cover all 6 nodes, so we needed 1 more level


   Number of levels required = ceil(log2(N)) + 1
   Number of nodes needed = 2^levels - 1
   Array size = 2^levels
```

### For the array `[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]`:
```
                                (1)
                        [1,2,3,4,5,6,7,8,9,10]
                        /                       \
                    (2)                           (3)
            [1,2,3,4,5]                     [6,7,8,9,10]
            /           \                   /           \
            (4)            (5)              (6)            (7)
        [1,2,3]         [4,5]           [6,7,8]         [9,10]
        /     \         /   \           /     \         /     \
        (8)    (9)     (10) (11)       (12)   (13)     (14)   (15)
    [1,2]   [3]     [4]  [5]       [6,7]  [8]      [9]    [10]
    /  \                           /  \
  (16) (17)                     (24) (25)
  [1] [2]                       [6]  [7]
```
---

# Segment Tree recursive

```cpp

const int maxN = 100001;
// const st_size = pow(2, (ceil(log2(maxN)) + 1));
int st[4 * maxN];
int lazy[4 * maxN];   //if lazy is present, it is not applied yet

void build(int node, int start, int end, int A[])   //build(1,0,n-1,a);
{
    if(start == end) st[node] = A[start];
    else
    {
        int mid = (start + end) / 2;
        build(2*node, start, mid, A);
        build(2*node+1, mid+1, end, A);

        st[node] = st[2*node] + st[2*node+1];
    }
}

//for lazy update
void update(int node , int start , int end , int l , int r , int val)
{
	if(lazy[node] != 0)
	{
		int dx = lazy[node];
		lazy[node] = 0;
		st[node] += dx * (end - start + 1);
		
		if(start != end)
		    lazy[2*node] += dx , lazy[2*node+1] += dx;
	}
	
	if(r < start || end < l) return;
	
	if(l <= start && end <= r)
	{
		int dx = (end - start + 1) * val;
		st[node] += dx;
		
		if(start != end)
		    lazy[2*node] += val , lazy[2*node+1] += val;
		return;
	}
	
	int mid = (start + end) / 2;
	update(2*node , start , mid , l , r , val);
	update(2*node+1 , mid+1 , end , l , r , val);
	
	st[node] = st[2*node] + st[2*node+1];
}


void update(int node, int start, int end, int idx, int val, int A[])
{	
    if(start == end) // Leaf node
    {
        A[idx] += val;
        st[node] += val;
    }
    else
    {
        int mid = (start + end) / 2;
        if(start <= idx and idx <= mid)
            update(2*node, start, mid, idx, val, A);
        else
            update(2*node+1, mid+1, end, idx, val, A);

        st[node] = st[2*node] + st[2*node+1];
    }
}

int query(int node, int start, int end, int l, int r)
{
    if(lazy[node] != 0)
    {
        int dx = lazy[node];
        lazy[node] = 0;
        st[node] += dx * (end-start + 1);

        if(start != end)
        lazy[2*node] += dx , lazy[2*node+1] += dx;
    }
 
    // range represented by a node is completely outside the given range
    if(r < start or end < l) return 0;
    
    if(l <= start and end <= r) return st[node];

    // range represented by a node is partially inside and partially outside the given range
    int mid = (start + end) / 2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node+1, mid+1, end, l, r);
    return (p1 + p2);
}

```