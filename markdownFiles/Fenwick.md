# [Binary Indexed Trees](https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/)

### Read
![](https://images.ctfassets.net/piwi0eufbb2g/6MTMWSoGHQcg6R7a5nsT8G/278635e8f83f93b2769cfacb3f4de7ce/read.gif)

```cpp
/*
(idx & -idx) will isolate the last bit
-num -> (a1b)¯ + 1      -> a¯0b¯ + 1 -> a¯0(0…0)¯ + 1 
     -> a¯0(1…1) + 1    -> a¯1(0…0)  -> a¯1b

fen[idx] will store the sum of values from ( a[idx - LSB(idx)], a[idx] ]
cumulative freq from 0-10 => tree[1010](10 & 9) + tree[1000](8 to 0)
*/
int prefix(vector<int>& fen, int idx) 
{
    int sum = 0;
    while (idx > 0) 
    {
        sum += fen[idx];

        // clearing lowest set bit in each iteration
        idx -= (idx & -idx);
        // idx &= idx - 1; // will also work
    }
    return sum;
}
```

---
### Update

![](https://images.ctfassets.net/piwi0eufbb2g/25Kj4cq7Ab9M6eBRyM8cfU/80c135356c9820412c84b9e65582ac83/bitupdate.gif)
```cpp

/*
changing a[10] or a[1010b] 
will only effect 1010, 1100, 10000, 100000 and so on be cause only 
these indexes, tree[1100], tree[10000]... stores the value of a[10]

a[0'0111'0100] -> fen[0'0111'0100, 0'0111'1000, 0'1000'0000, 1'0000'0000]
fen[0'0111'0100] -> a[0'0111'0100] upto a[0'0111'0000]
fen[0'0111'1000] -> a[0'0111'1000] upto a[0'0111'0000]
fen[0'1000'0000] -> a[0'1000'0000] upto a[0'0000'0000]
*/
void update(vector<int>& fen, int N, int idx, int val) 
{
    while (idx <= N) 
    {
        fen[idx] += val;
        idx += (idx & -idx);
    }
}
```

---

### To read a single value
![](https://images.ctfassets.net/piwi0eufbb2g/7N1GelGEUWMWqK5NAejfsg/e08316d27d55af28ff7f8f6fd58eaa49/reada.gif)
- example getting the actual frequency for index 12, i.e. a[12]


```cpp

int readSingle(vector<int>& fen, int idx) 
{
    int sum = fen[idx]; // this sum will be decreased
    if (idx > 0) { // the special case
        int z = idx - (idx & -idx);
        idx--; // idx is not important anymore, so instead y, you can use idx
        while (idx != z) { // at some iteration idx (y) will become z
            sum -= fen[idx];
            // subtract tree frequency which is between y and "the same path"
            idx -= (idx & -idx);
        }
    }
    return sum;
}
```

### Lower & Upper bounds

```cpp
// only for non -ve freq 
// (that means cumulative frequencies for greater indices are not smaller)

// Find smallest index such that prefix_sum >= target
// Returns N+1 if not found
int lower_bound(int target) {
    //remove below line for upper_bound (prefix_sum > target)
    if (target <= 0) return 1;  // All indices satisfy if target <= 0
    
    int idx = 0;    // Max idx where prefix_sum < target
    int sum = 0;    // Cumulative sum

    for (int bit = 1 << (int)log2(N); bit; bit >>= 1) {
        //change condition to <= for upper_bound
        if (idx + bit <= N && sum + fen[idx + bit] < target) {
            sum += fen[idx + bit];
            idx += bit;
        }
    }
    return idx + 1;
}
```