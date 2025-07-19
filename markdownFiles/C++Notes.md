### **Lvalues (Locator Values)**
- **Definition:** Objects with a **name** and **memory address** (persistent).
- **Characteristics:**  
  ✅ Can appear on **both sides** of `=`.  
  ✅ Can be modified (unless `const`).  
  ✅ Address can be taken (`&x`).  
- **Examples:**  
  ```cpp
  int x = 10;       // 'x' is an lvalue
  int* p = &x;      // Address taken
  x = 20;           // Modifiable
  ```

### **Rvalues (Right-Hand Values)**
- **Definition:** Temporary objects with **no persistent storage**.
- **Characteristics:**  
  ❌ Can **only** appear on the **right side** of `=`.  
  ❌ Cannot be modified (`5 = x` is invalid).  
  ❌ Cannot take address (`&5` is invalid).  
- **Examples:**  
  ```cpp
  int y = 5 + 3;    // '5 + 3' is an rvalue
  std::string s = getName(); // 'getName()' returns an rvalue
  ```

---

### **Lvalue Reference (`&`)**
- Binds **only to lvalues**.
- Used for **modifying existing objects**.
```cpp
int a = 5;
int& ref = a;   // OK, 'a' is an lvalue
// int& bad = 10; // Error: Cannot bind to rvalue
```

### **Rvalue Reference (`&&`)**
- Binds **only to rvalues**.
- Enables **move semantics** (efficient resource transfer).
```cpp
int&& rref = 10;          // OK, '10' is an rvalue
// int&& bad = a;         // Error: Cannot bind to lvalue
std::string&& sref = getName(); // Binds to temporary
```
---

## Move Semantics (Avoiding Unnecessary Copies)
### **Problem: Expensive Copies**
Before C++11, copying large objects (e.g., `std::vector`) was inefficient:
```cpp
std::vector<int> createVector() {
    std::vector<int> v(1000000, 42); // Large vector
    return v; // Copy (slow) in C++03, move (fast) in C++11+
}
```

### **Solution: Move Constructor & `std::move`**
- **Move Constructor (`T(T&& other)`)**  
  - Steals resources from `other` (no deep copy).
- **`std::move`**  
  - Converts an **lvalue → rvalue** to enable moving.
```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = std::move(v1); // v1 is now empty (resources moved)
```

#### **Key Points:**
✔ After moving, the source object (`v1`) is **valid but unspecified** (usually empty).  
✔ Used in STL containers (`std::vector`, `std::string`, etc.) for efficiency.  

---

## Perfect Forwarding (`std::forward`)
### **Problem: Reference Collapse in Templates**
When forwarding arguments in templates, we **lose** the original lvalue/rvalue nature:
```cpp
template<typename T>
void wrapper(T arg) {
    someFunction(arg); // Always passes as lvalue (bad!)
}
```

### **Solution: Forwarding/Universal Reference (`T&&`) + `std::forward`**
- **Universal Reference (`T&&`)**  
  - Works for **both lvalues and rvalues**.
- **`std::forward<T>(arg)`**  
  - Preserves the original value category.
```cpp
template<typename T>
void wrapper(T&& arg) {
    someFunction(std::forward<T>(arg)); // Keeps lvalue/rvalue
    // Loses information about whether original argument was lvalue/rvalue
    // Can't properly forward if someFunction is overloaded on T& and T&&
}
```

#### **Example: `emplace_back` in STL**
```cpp
std::vector<std::string> vec;
vec.emplace_back("Hello"); // Constructs in-place:
// 1. "Hello" is rvalue (const char[6])
// 2. Perfectly forwarded to std::string constructor
// 3. No temporary string created
```
---

<br /> 
<br /> 
<br /> 


# Recursive Lambdas in C++

```cpp
auto dfs = [&](int u) -> int {  // Explicit return type
    print(__PRETTY_FUNCTION__);
    return u;
};
```

### Capture Clauses Explained

1. `[]` - Empty capture: can only access local lambda variables
2. `[&]` - Capture all variables by reference: can modify variables from outer scope
3. `[=]` - Capture all variables by value(makes a copy at the moment lambda is defined): read-only access to outer variables
4. `[a, &b]` - Mixed capture: `a` by value, `b` by reference
5. `[this]` in the capture refers to the lambda's *own closure object*.


## The Recursive Lambda Problem
In C++ (pre-C++23), writing recursive lambdas requires special handling because:
1. A lambda can't directly call itself in its body (the name isn't in scope yet)
2. We need a way to pass the lambda to itself for recursion

#### Deduction Error:
```cpp
auto dfs = [&](int u) {
    dfs(v);  // Error: use of 'dfs' before deduction of 'auto'
};
```

## Solutions

#### 1. Traditional Solution (C++17/20)
```cpp
auto dfs = [&](auto &&self, int node) -> void {
    for (int child : adj[node]) {
        self(self, child);  // Pass self to itself
    }
};

// Initial call
dfs(dfs, start_node);  // Must pass the lambda to itself
```


- **`auto &&self` is a *forwarding reference*** (often called a "universal reference").
- Works whether you pass the lambda as an lvalue or rvalue:
    ```cpp
    dfs(dfs, node);          // lvalue (common case)
    std::move(dfs)(dfs, node); // rvalue (rare but valid)
    ```
- Follows the same rules as `T&&` in template deduction.

- When you call `dfs(dfs, node)`, `auto` deduces to the lambda's type, making `self` an lvalue reference.

- If it were `int &&`, it would *only* bind to rvalues.
- But with `auto&&` (or template `T&&`), it adapts to the input.

   

- **No Lifetime Issues**:
  The lambda exists for the entire recursion, so dangling references aren't a concern here.

- **❌ Not Actually Needed**:
    For recursion, you could use `auto self` (by-value) or `auto &self` (by lvalue reference) instead of `auto &&self`, but `&&` is conventional because:
    1. It's the most general form.
    2. Matches the pattern used in generic code (e.g., `std::forward`).

---



#### 2. Using std::function (Alternative)
```cpp
vector<bool> mark(Alp);
function<void(int)> dfs = [&](int u) {
    mark[u] = true;
    for (auto v : adj[u])
        if (!mark[v])
            dfs(v);  // Now can call directly
};
```

- `std::function` allows recursive calls by name
- Slightly less efficient due to type erasure
- More readable syntax

#### 3. C++23 Simplified Syntax
```cpp
auto dfs = [&, this](int node) -> void {
    for (int child : adj[node]) {
        dfs(child);  // Direct recursion now works
    }
};

// Initial call
dfs(start_node);
```

- `this` in capture enables recursive calls


## References

- [N3424: Documenting the self-recursive lambda idiom](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3424.pdf)
---

<br /> 
<br /> 
<br /> 

# `constexpr` vs `const` vs `consteval` in C++

#### **`const` (Constant)**  
- **Purpose**: Makes a variable read-only (cannot be modified after initialization).  
- **Initialization**: Can be set at **runtime or compile-time**.  
- **Key Points**:  
  - Ensures immutability.  
  - Cannot be used where compile-time values are required (e.g., array sizes in standard C++).  

---

#### **`constexpr` (Constant Expression)**  
- **Purpose**: Ensures a value is computed **at compile-time**.  
- **Initialization**: Must be set with **compile-time known values**.  
- **Usage**:  
  ```cpp
  constexpr int x = 5;           // OK  
  constexpr int y = sqrt(9);     // OK if `sqrt` is constexpr  
  constexpr int z = rand();      // Error: Not computable at compile-time  
  ```  
- **Key Points**:   
  - Required in contexts needing compile-time values (e.g., array sizes, template args).  
  - Functions marked `constexpr` must be evaluable at compile-time, _if given_ `constexpr` arguments, but they can also be used at runtime with _non-constexpr_ arguments.


- **"Maybe" compile-time**: Can run at either compile-time or runtime
- **Flexible**: Functions can be called in both contexts
- **Example**:
  ```cpp
  constexpr int square(int x) { return x * x; }
  
  int main() {
      constexpr int a = square(5);  // Compile-time
      int b = square(get_input());  // Runtime
  }
  ```
---

#### `consteval` (C++20)
- Can only be applied to functions, not variables.  
- **"Always" compile-time**: Must run at compile-time
- **Strict**: Functions can only be called in constant expressions
- **Example**:
  ```cpp
  consteval int cube(int x) { return x * x * x; }
  
  int main() {
      constexpr int c = cube(3);  // OK
      int d = cube(get_input());  // Error! Must be compile-time
  }
  ```
<br/>
<br/>
<br/>

# Containers in C++

Containers in C++ are data structures provided by the Standard Template Library (STL) that store collections of objects (elements). They manage the storage space for their elements and provide member functions to access and manipulate them.

### 1. Sequence Containers (maintain element order)
- `vector`: Dynamic array (fast random access, efficient insertion at end)
- `array`: Fixed-size array (stack-allocated, size known at compile time)
- `deque`: Double-ended queue (fast insertion at both ends)
- `list`: Doubly-linked list (efficient insertion/removal anywhere)
- `forward_list`: Singly-linked list (memory-efficient for one-way traversal)

### 2. Associative Containers (sorted by key)
- `set`: Collection of unique keys, sorted
- `multiset`: Collection of keys (duplicates allowed), sorted
- `map`: Key-value pairs with unique keys, sorted by key
- `multimap`: Key-value pairs (duplicate keys allowed), sorted by key

### 3. Unordered Associative Containers (hash-based)
- `unordered_set`: Hash table implementation of set
- `unordered_multiset`: Hash table implementation of multiset
- `unordered_map`: Hash table implementation of map
- `unordered_multimap`: Hash table implementation of multimap

### 4. Container Adapters (special interfaces)
- **You can't iterate over them.**
- `stack`: LIFO (Last-In First-Out) structure
- `queue`: FIFO (First-In First-Out) structure
- `priority_queue`: Elements with highest priority come out first

### 5. Special Containers
- `bitset`: Fixed-size sequence of bits
- `valarray`: Optimized for numeric operations
- `string`: Specialized for character sequences
