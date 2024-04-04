//https://www.hackerearth.com/zh/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
 //https://www.youtube.com/watch?v=BuoG-1KC4qs --- laoduchand 
//for lazy - https://www.youtube.com/watch?v=wQSnKUs93DU&list=PL2q4fbVm1Ik6v2-emg_JGcC9v2v2YTbvq&index=8


i think 2*maxN space will also work with this implementation, not sure tho but looks like it
[1,2,3,4,5]         -> 1

2       3
[1 2 3]  [4 5]

4       5   6   7
[1 2] [3]   [4] [5]

8   9
[1] [2]


const int maxN = 100001;
int st[4*maxN] , lazy[4*maxN];

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
	
	if(l<=start && end <= r)
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
    if(start == end)
    {
        // Leaf node
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
        // Internal node will have the sum of both of its children
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
 
    if(r < start or end < l)
    {
        // range represented by a node is completely outside the given range
        return 0;
    }
    if(l <= start and end <= r)
    {
        // range represented by a node is completely inside the given range
        return st[node];
    }
    // range represented by a node is partially inside and partially outside the given range
    int mid = (start + end) / 2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node+1, mid+1, end, l, r);
    return (p1 + p2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);



    return 0;
}
