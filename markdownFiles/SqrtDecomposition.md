worst case complexity should be `O( (N-2)/B + 2*B )`, optimal block size = `sqrt( (N-2)/2 )` when `(n-2)/B = 2B`. Standard we take $O(N/B + B)$.

```cpp
class SquareRootDecomposition {
private:
    vector<int> arr;
    int block_size;
    vector<int> block_sum;

public:
    SquareRootDecomposition(const vector<int>& input) : arr(input) {
        int n = arr.size();
        block_size = static_cast<int>(ceil(sqrt(n)));
        int num_blocks = (n + block_size - 1) / block_size;
        block_sum.resize(num_blocks, 0);
        
        for (int i = 0; i < n; ++i) {
            int block_idx = i / block_size;
            block_sum[block_idx] += arr[i];
        }
    }

    // Update value at index and maintain block sums
    void update(int index, int new_value) {
        int delta = new_value - arr[index];
        arr[index] = new_value;
        int block_idx = index / block_size;
        block_sum[block_idx] += delta;
    }

    int query(int l, int r) {
        int sum = 0;
        int block_l = l / block_size;
        int block_r = r / block_size;

        if (block_l == block_r) {
            for (int i = l; i <= r; ++i)
                sum += arr[i];
        } else {
            // Left partial block
            int end_left = (block_l + 1) * block_size - 1;
            if(l == block_l * block_size) 
                sum += block_sum[block_l];
            else 
                for (int i = l; i <= end_left; ++i)
                    sum += arr[i];

            // Right partial block
            int start_right = block_r * block_size;
            if(r != (block_r + 1) * block_size - 1)
                for (int i = start_right; i <= r; ++i)
                    sum += arr[i];
            else sum += block_sum[block_r];

            // Complete middle blocks
            for (int b = block_l + 1; b < block_r; ++b)
                sum += block_sum[b];
        }
        return sum;
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SquareRootDecomposition sr(arr);

    cout << "Original array:\n";
    cout << sr.query(2, 7) << "\n";  // Output: 33
    cout << sr.query(0, 9) << "\n";  // Output: 55

    // Update index 4 (value 5) to 100
    sr.update(4, 100);
    cout << "\nAfter update:\n";
    cout << sr.query(4, 4) << "\n";  // Output: 100
    cout << sr.query(2, 7) << "\n";  // Output: 128 (3+4+100+6+7+8)
    cout << sr.query(0, 9) << "\n";  // Output: 150

    return 0;
}
```
---

# [Mo's algorithm](https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm)

- Read above article, explained very well there.
- For  `BLOCK_SIZE` $ \approx \sqrt{N}$  this gives  
$O((N + Q) \sqrt{N})$  operations in total. Thus the complexity is  
$O((N+Q)F\sqrt{N})$  where  
$O(F)$  is the complexity of add and remove function.
- For each $Q$ - **left** pointer can move $\sqrt{N}$ distance, and for each _BLOCK_ - **right** pointer can move $N$ distance.

Below is code for [Mode-Queries](https://leetcode.com/problems/threshold-majority-queries/description/).
```
Bit faster approach of below code -

Maintain two structures:
A priority_queue (max-heap) storing (frequency, value) pairs.
A hash map (freq) storing the current true frequency of each element.

When inserting/updating:
Push the new (frequency, value) into the heap (even if it’s a duplicate).
Update freq[x].

When querying the mode (get_answer):
While the top of the heap has a frequency ≠ true frequency (freq[top.second] != top.first), pop it (lazy deletion).
The first valid top is the mode.
```
---
Maintain data structures
```cpp
bool Compare(pair<int, int>& p, pair<int, int>& q) {
    if (p.first != q.first) 
        return p.first > q.first;
    else 
        return p.second < q.second;
}

unordered_map<int, int> freq;
set<pair<int, int>, decltype(&Compare)> freq_set(Compare);

void add(int x) {
    if (freq[x] > 0) freq_set.erase({freq[x], x});
    freq[x]++;
    freq_set.insert({freq[x], x});
} 

void remove(int x) {
    freq_set.erase({freq[x], x});
    freq[x]--;
    if (freq[x] > 0) freq_set.insert({freq[x], x});
}

int get_answer() {
    return (*freq_set.begin()).second;
} 
```
---
Actuall Mo's algo
```cpp
int block_size;

struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

//more optimized than operator< of Query
bool cmp(Query& p, Query& q) {
    if (p.l / block_size != q.l / block_size)
        return p < q;
    return (p.l / block_size & 1) ? (p.r < q.r) : (p.r > q.r);
}

vector<int> cow(vector<int>& a, vector<Query> queries) {

    freq.clear(); freq_set.clear();

    int n = a.size();
    block_size = static_cast<int>(ceil(sqrt(n)));

    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end(), cmp);  //override the Query< operator


    int cur_l = 0;
    int cur_r = -1;
    // range [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(a[cur_l]);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(a[cur_r]);
        }
        while (cur_l < q.l) {
            remove(a[cur_l]);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(a[cur_r]);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}
```

TODO - Checkout [more faster](https://codeforces.com/blog/entry/61203) sorting order.