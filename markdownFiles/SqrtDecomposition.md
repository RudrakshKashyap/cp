dont know , just copy pasted from somewhere
looks correct to me


Sqrt Decomposition Algorithm can be extended to a point update and for range query. 
Here both of these are in implementation using sum range 

complexity should be `O( (N-2)/B + 2*B )`, optimal block size = `sqrt( (N-2)/2 )` when (n-2)/B = 2B

```cpp
//code by deepseek
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

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
            for (int i = l; i <= end_left; ++i)
                sum += arr[i];

            // Right partial block
            int start_right = block_r * block_size;
            for (int i = start_right; i <= r; ++i)
                sum += arr[i];

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
