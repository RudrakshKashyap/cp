
# Dangling Pointers

* When you create a local variable (like last), it is allocated on the stack. Stack memory is automatically reclaimed when the function exits, and the object is destroyed.
* Storing a pointer to a stack-allocated object outside its scope (e.g., in a linked list or a map) is unsafe because the object will no longer exist after the function exits.
	```cpp
	void put(int key, int value) {
	    Node newNode(key, value);	//Will be allocated on stack and gets deleted after function return
	    mp[key] = *tail;
	    tail->next = &newNode; // Link the new node to the list
	    tail = tail->next; // Update tail to the new node
	}
	```
* Correct Approach (this is also wrong check below for common error) -> 

	```cpp
	void put(int key, int value) {
	    Node* newNode = new Node(key, value); // Allocate on the heap
	    mp[key] = *tail; // Store the previous tail in the map
	    tail->next = newNode; // Link the new node to the list
	    tail = tail->next; // Update tail to the new node
	}
	```
# CAUTION when using Map
- **Most STL containers (`vector`, `set`, `map`, `queue`, etc.) store copies** of objects by default.  
- **If you want reference semantics**, you must explicitly use pointers (`std::shared_ptr<T>`, `std::unique_ptr<T>`) or `std::reference_wrapper<T>`.  
- **Container adapters (`stack`, `queue`, `priority_queue`) also store copies**.  
```cpp
map<int, Node> mp;
Node newNode(3);
mp[3] = newNode; //map will store the copy of the newNode, modifying map[3] will not modify newNode
```
If the key does not exist in the map:
* `mp[key]` inserts a new key-value pair into the map.
* The value is default-constructed (if non pointer type, this is why default constuction is important of struct or class).
* The map manages its own memory, so it needs to store its own copies of objects to ensure they remain valid even if the original object is modified or destroyed.
* The size of the map increases by 1.
* calling `[] operator` frequently will keep on increasing memory, resulting in MLE or runtime error
* The find method does not modify the map. It returns an iterator to the element if the key is found, otherwise it returns `end()`.

# CAUTION when making CustomComparators
```cpp
/*
	buggy comparator eg -> 
	For elements (1,1) and (2,2):
	Compare((1,1), (2,2))   1>2? false → 1<2? true → true
	Compare((2,2), (1,1))   2>1? true → true
*/
bool Compare(const pair<int, int>& p, const pair<int, int>& q) {
    if (p.first > q.first) return true;
    return p.second < q.second;
}

//FIXED
bool Compare(const pair<int, int>& p, const pair<int, int>& q) {
    if (p.first != q.first) 
        return p.first > q.first;
    else 
        return p.second < q.second;
}
```

# STL errors

**Floating-Point Representation (IEEE 754)**
A double has 53 bits of precision (~15-17 decimal digits).<br/>
For numbers as large as `1e18`, the smallest representable difference between two values is __128__ (not `1`).

```cpp
double x = 1e18, y = 1e18;
x += 64, y += 65;
print((ll) x, (ll) y);	// prints 1e18, 1e18 + 128

ll a = 1e18 + 1; // WRONG
ll a = (ll)1e18 + 1; // CORRECT
```
---

```cpp
//for set/multisets
set.erase(set.rbegin()); // ERROR --> erase expect fwd iterator
if(!s.emtpy()) s.erase(prev(s.end()));  //correct
```
---

```cpp
vector<pair<int, int>> ans;
vec.emplace_back({1, 2}); // ERROR --> if you're trying to createa a pair
/*
The issue is that emplace_back() uses perfect forwarding and template argument deduction.
emplace_back is a template function that needs to deduce the arguments for pair's constructor

When you pass {1, 2}, the compiler doesn't have enough context to deduce that this should be a pair<int, int> because:
1. A braced initializer list (like {1, 2}) is typeless by itself.
2. It can be converted to many types (e.g., pair<int,int>, array<int,2>, initializer_list<int>), but the compiler cannot deduce which one you want without context.
*/
vector<vector<int>> ans;
ans.emplace_back({1, 2});  // works
```
---

```cpp
/*
set provides bidirectional iterators (can do ++/--), but not random-access iterators (cannot do iterator + offset in O(1)).
*/
lower_bound(set.begin(), set.end(), x); //O(n) n/2 + n/4 + n/8.. for set(sorted)
set.lower_bound(x); // O(log n)
```
---
**Avoid `#define` for type aliases**
```cpp
// ❌ Dangerous
#define INT_PTR int*

INT_PTR a, b;  // Becomes int* a, b; (b is int, not int*!)

// ✅ Safe
using IntPtr = int*;
IntPtr a, b;  // Both are int*
```