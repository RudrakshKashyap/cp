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
void someFunction(int&)  { cout << "lvalue\n"; }
void someFunction(int&&) { cout << "rvalue\n"; }

template<typename T>
void wrapper(T arg) {
    // Loses information about whether original argument was lvalue/rvalue
    // Can't properly forward if someFunction is overloaded on T& and T&&
    someFunction(arg); // Always passes as lvalue (bad!)
}
```

### **Solution: Forwarding/Universal Reference (`T&&`) + `std::forward`**

- **Universal Reference (`T&&`)**

  - **`T&&` is a forwarding reference (not rvalue ref)**
  - Works for **both lvalues and rvalues**.
  - ✅ If an **lvalue** is passed, `T` deduces as `T&`(only in case of fwd ref), and `T&&` collapses to `T&`.
  - ✅ If an **rvalue** is passed, `T` deduces as `T`, and `T&&` stays `T&&`.

- **`std::forward<T>(arg)`**
  - Preserves the original value category.

```cpp
template<typename T>
void wrapper(T&& arg) {
    someFunction(std::forward<T>(arg)); // Keeps lvalue/rvalue
}
int main() {
    int x = 10;
    wrapper(x);           // Calls someFunction(int&)  → prints "lvalue"
    wrapper(42);          // Calls someFunction(int&&) → prints "rvalue"
    wrapper(std::move(x));// Calls someFunction(int&&) → prints "rvalue"
}
```

---

## **`push_back` vs `emplace_back` in STL**

```cpp
vector<string> vec;
vec.emplace_back("Hello"); // Constructs in-place
// 1. "Hello" is rvalue (const char[6])
// 2. Perfectly forwarded to std::string constructor
// 3. No temporary string created

struct Node {
    int key, val;
    Node(int k, int v) : key(k), val(v), next(nullptr) {} // Constructor 1
};
vector<Node> vec;
vec.emplace_back(2, 5); //will call constructor and add a Node(2, 5)
```

| Scenario                                        | `push_back(obj)`                       | `emplace_back(args...)`               |
| ----------------------------------------------- | -------------------------------------- | ------------------------------------- |
| **Passing an existing object** (`obj`)          | Copies (if lvalue) / Moves (if rvalue) | Same as `push_back` (copies/moves)    |
| **Passing constructor args** (`1, "foo"`)       | ❌ Not possible                        | ✅ Constructs in-place (no copy/move) |
| **Performance** (when constructing new objects) | May involve extra copy/move            | More efficient (constructs directly)  |


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
5. `[this]` in the capture refers to the lambda's _own closure object_.

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
auto dfs = [&](auto&& self, int node) -> void {
    for (int child : adj[node]) {
        self(self, child);  // Pass self to itself
    }
};

// Initial call
dfs(dfs, start_node);  // Must pass the lambda to itself
```

- **`auto&& self` is a _forwarding reference_** (often called a "universal reference").
- Works whether you pass the lambda as an lvalue or rvalue:
  ```cpp
  dfs(dfs, node);          // lvalue (common case)
  std::move(dfs)(dfs, node); // rvalue (rare but valid)
  ```
- Follows the same rules as `T&&` in template deduction.

- When you call `dfs(dfs, node)`, `auto` deduces to the lambda's type, making `self` an lvalue reference.

- If it were `int&&`, it would _only_ bind to rvalues.
- But with `auto&&` (or template `T&&`), it adapts to the input.

- **No Lifetime Issues**:
  The lambda exists for the entire recursion, so dangling references aren't a concern here.

- **❌ Not Actually Needed**:
  For recursion, you could use `auto self` (by-value) or `auto& self` (by lvalue reference) instead of `auto&& self`, but `&&` is conventional because:
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

#### 3. C++23 (GCC 13+) Simplified Syntax

```cpp
auto dfs = [&, this](int node) { // 'this' is optional if not in a class
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

# Y combinator - TODO

```cpp
//https://www.youtube.com/watch?v=9T8A89jgeTI&ab_channel=Computerphile
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

y_combinator([&](auto recurse, int start, int end) -> void {
        if (start >= end)
            return;

        if (!done.emplace(start, end).second)
            return;

        sums.insert(prefix_sum[end] - prefix_sum[start]);
        int minimum = A[start];
        int maximum = A[end - 1];
        int cutoff = (minimum + maximum) / 2;
        int split = int(upper_bound(A.begin(), A.end(), cutoff) - A.begin());
        recurse(start, split);
        recurse(split, end);
    })(0, N)
```

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

- **For values**:

  - Ensures a value is computed **at compile-time**.
  - Must be set with **compile-time known values**.
    ```cpp
    constexpr int x = 5;           // OK
    constexpr int y = sqrt(9);     // OK if `sqrt` is constexpr
    constexpr int z = rand();      // Error: Not computable at compile-time
    ```
  - Required in contexts needing compile-time values (e.g., array sizes, template args).

- **For functions**:

  - Functions marked `constexpr` must be evaluable at compile-time, _if given_ `constexpr` arguments, but they can also be used at **runtime** with _non-constexpr_ arguments.

  - **"Maybe" compile-time**: Can run at either compile-time or runtime
  - **Flexible**: Functions can be called in both contexts

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

Containers in C++ are data structures provided by the Standard Template Library (STL) that store collections of objects (elements). They manage the storage space for their elements and provide member functions to access and manipulate them. `pair` & `tuples` are not containers, because they lack iterators and standard container interfaces.

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

- `bitset`: Fixed-size sequence of bits (stores bits)
- `valarray`: Optimized for numeric operations
- `string`: Specialized for character sequences (stores chars)
---

  <br/>
  <br/>
  <br/>

# `std::tie` in C++

`std::make_tuple` creates a tuple of values but <br/>
`std::tie` is a utility function from the <tuple> header that creates a tuple of lvalue references, e.g.

```cpp
int a = 1, b = 2, c = 3;
    
// Creates a tuple of references to a, b, c
auto t = std::tie(a, b, c);  

// Modifying through the tuple modifies the original variables
get<0>(t) = 10;
cout << a;  // Outputs 10

//comparing tuples in comparator
tie(x, type) < tie(other.x, other.type) 
```
---
<br />
<br />

# `typedef` vs `using` vs `#define`


- **Use `using`** for all type aliasing needs (modern, readable, powerful)
- **Avoid `typedef`** for new code (legacy compatibility only)
- **Minimize `#define`** for type aliases (use only for simple constants or conditional compilation)

| Feature | `using` | `typedef` | `#define` |
|---------|---------|-----------|-----------|
| Type safety | ✅ | ✅ | ❌ |
| Scope awareness | ✅ | ✅ | ❌ |
| Template support | ✅ | ❌ (needs workaround) | ❌ |
| Namespace support | ✅ | ✅ | ❌ |
| Readability | ✅ | ⚠️ | ❌ |
| Debugging | ✅ | ✅ | ❌ |


### Scope and Namespace Awareness
```cpp
namespace MyNamespace {
    typedef int Integer;
    using Float = float;
}

// #define INTEGER int  // Global, cannot be namespaced

MyNamespace::Integer x;  // Works
MyNamespace::Float y;    // Works
// INTEGER z;           // Global pollution
```

### `#define` (Preprocessor Macro)

**Syntax:**
```cpp
#define ALIAS_NAME replacement_text
```
**Major Disadvantages:**
- Text substitution (no type safety)
- Scope issues (global unless `#undef`)
- Debugging difficulties
- No namespace awareness

---
<br />
<br />

## `int64_t`
- **int64_t**: This is a standard C++ type defined in the <cstdint> header (or <stdint.h> in C). It guarantees a signed integer type of exactly 64 bits in size. This fixed width ensures consistent behavior and data representation across various systems and compilers that adhere to the C++ standard. This makes `int64_t` highly portable and reliable for situations where a precise 64-bit integer is required.
- **int64**: This is not a standard C++ type. Before `int64_t` was introduced in the C++ standard, many compilers and projects implemented their own custom 64-bit integer types, often named `int64`, `__int64`, or using `long long`. The behavior and actual size of `int64` could vary depending on the specific compiler and platform. While it might represent a 64-bit integer on many modern systems, there's no guarantee of this across all environments or older compilers.
