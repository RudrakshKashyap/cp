### **Custom Comparator for `priority_queue`**

- **Internal Representation:**  
  Elements are stored in a **max-heap** (default), where the largest element is at the top.  
  Example: `[0, 1, 2, 3, 4]` is arranged as:
  ```
        4
      /   \
     2     3
    / \
   0   1
  ```
  - **Top element:** `4` (highest priority).
  - **No direct access** to other elements.

---

- **Syntax for Comparator Function:**
  ```cpp
  bool Compare(Node a, Node b);  // Custom comparison function
  ```
- **Declaring `priority_queue` with Custom Comparator:**
  ```cpp
  // Passing the type (decltype) and the actual function
  std::priority_queue<Node, std::vector<Node>, decltype(&Compare)> openSet(Compare);
  ```

- **Using a Functor (Struct with `operator()`):**
  ```cpp
  struct comp {
    //Q: Can we place element b at the top
      bool operator()(int const a, int const b) const {
          return a < b;  // Max-heap behavior
      }
  };

  std::priority_queue<int, std::vector<int>, comp> pq;
  ```
  - **Why Functor?**  
    The `priority_queue` expects the `Compare` parameter to be a **callable type** (like a function object). A struct with `operator()` satisfies this.

---

#### **Advanced Custom Comparator Example**
- **Comparator Using External Data:**
  ```cpp
  //can use struct also
  class comp {
      int* b;  // Pointer to an external array
  public:
      comp(vector<int>& a) { b = &a[0]; }  // Initialize with external data
      bool operator()(ar o1, ar o2) {
          // Custom comparison logic
          return b[o1[0]] * b[o2[1]] > b[o2[0]] * b[o1[1]];
      }
  };

  int main() {
      vector<int> arr = {2, 3, 5};
      priority_queue<ar, vector<ar>, comp> pq(arr);  // Pass external data
      pq.push({0, 1});  // Insert pairs
      // ...
  }
  ```
  **Output:** `{0, 2} {1, 2} {0, 1}` (Order based on custom comparator).

---
<br />
<br />
<br />

### **Functor for Sorting (e.g., `std::sort`)**
- **Example: Sort strings by length (ascending):**
  ```cpp
  struct customCompFunctor {
    //Q: Can we place element b at the end
    //A: yes if it is big in case of ascending order
      bool operator()(const string& a, const string& b) const {
          return a.length() < b.length();
      }
  };

  // Usage in sort:
  sort(words.begin(), words.end(), customCompFunctor());
  ```
  - **Note:** `customCompFunctor()` creates a temporary instance for comparison. <br />
  To access the actual function you can do `bool x = customCompFunctor()("a", "b");`

---
<br />
<br />
<br />

### **Custom Comparator for Suffix Arrays**
- **Example: Compare subarrays for pattern searching:**
  ```cpp
  vector<int> v1;  // Global/class member for comparator access

  bool comp(int i1, vector<int> v2) {
      int len1 = v1.size() - i1;
      int len2 = v2.size();
      int len = min(len1, len2);
      for (int i = 0; i < len; i++)
          if (v1[i1 + i] != v2[i])
              return v1[i1 + i] < v2[i];
      return len1 < len2;
  }

  // Usage in lower_bound for suffix array:
  lower_bound(suffixArray.begin(), suffixArray.end(), pattern, comp);
  ```
- **Purpose:** Finds occurrences of `pattern` in a suffix array.
    ```cpp
    int findNumberOfOccurences(vector<int> v, vector<int> &pattern) {
        if (pattern.size() == 0) return v.size() + 1;

        v.push_back(IntMinVal);
        vector<int> suffixArray = sa(v);

        v1 = v;

        auto it1 = lower_bound(suffixArray.begin(), suffixArray.end(), pattern, comp);
        pattern.back()++;
        auto it2 = lower_bound(suffixArray.begin(), suffixArray.end(), pattern, comp);

        return it2 - it1;
    }
    ```
---
