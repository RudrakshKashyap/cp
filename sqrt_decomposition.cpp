dont know , just copy pasted from somewhere




/// Sqrt Decomposition Algorithm can be extended to a point update and for range query. 
/// Here both of these are in implementation using sum range 


int block_size;/// the size of every block
int block_value[1001];///sqrt size of max 
int arr[1000001];

int query(int l,int r)
{
    int sum = 0;
    int start_block = l / block_size;///from which block,the query starts
    int  end_block = r / block_size;///in which block,the query stops
    int end_range_of_start_block=(start_block+1)*block_size-1;
    ///the before index of next block

   ///if both the starting and closing ranges are in same block,simply iterating,maximum complexity O(sqrt(n))
   if (start_block == end_block){
    for (int i=l; i<=r; ++i)
        sum += arr[i];
   }
  ///if both the starting and closing ranges in different blocks
  ///Then iterate the elements from first block and from last block linearly ,maximum sqrt(n)+sqrt(n)=2*sqrt(n).
  ///And iterate through over the values of interval blocks
  else
    {
    ///time complexity O(sqrt(n))
    for(int i=l; i<=end_range_of_start_block; ++i)
        sum += arr[i];
///as the block numbers can be maximum sqrt(n), so time complexity O(sqrt(n)-2)
    for(int i=start_block+1; i<=end_block-1; ++i)
        sum += block_value[i];
    ///time complexity O(sqrt(n))
    for (int i=end_block*block_size; i<=r; ++i)
        sum += arr[i];
    }
    return sum;
///Total Complexity O(sqrt(n)) + O(sqrt(n)) + O(sqrt(n)-2) approximately closely to O(sqrt(n))
}

/// adding val into index idx
void update(int idx, int val)
{
    ///in which block idx remains
    int blockNumber = idx / block_size;
    block_value[blockNumber] += val; /// adding value to the desired block
    arr[idx]+= val; /// adding
}
